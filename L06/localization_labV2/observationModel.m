%pM stands for probability map, map is the input map showing where obstacles
%and tennis balls are located, measurement is the reading from the sensor
%pipeline. In the simulator case this is a n by 2 matrix where the first
%column is the bearing to an observed tennis ball and the second column is
%the range to a observed tennis ball. 
function [pM] = observationModel(map,measurement,pM)
global DX;        %discretization along x axis
global DY;       %discretization along y axis
global DTH;      %discretization along th

%TODO given the measurement, map, and current probability map update the
%probability map 

%step 1: take noise out of measurements @_@ 
%specifically, the measurements seem to be a very noisy picture
% of just one or two tennis balls
oldPM = pM;

numMeasures = size(measurement);

if (numMeasures == 0)
    return;
end    
    
possibleBalls = [measurement(1,1),0,0;
                 measurement(1,2),0,0;
                 1,0,0];
numBalls = 1;
maxDelta = .3;
for i = 2:numMeasures
    bear = measurement(i,1);
    range = measurement(i,2);
    deltaRange = range - possibleBalls(2,numBalls);
%    disp(deltaRange);
    stop = 0;
    for j = 1:numBalls
        if (abs(deltaRange) < maxDelta)
            possibleBalls(1,j) = possibleBalls(1,j) + bear;
            possibleBalls(3,j) = possibleBalls(3,j) + 1;
            stop = 1;
        end
        if (stop) continue; end
    end
    if (stop) continue; end
    if (abs(deltaRange) > maxDelta)
        numBalls = numBalls + 1;
        possibleBalls(2,numBalls) = bear;
        possibleBalls(2,numBalls) = range;
        possibleBalls(3,numBalls) = 1;
    else
        possibleBalls(1,numBalls) = possibleBalls(1,numBalls) + bear;
        possibleBalls(3,numBalls) = possibleBalls(3,numBalls) + 1;
    end
end

ball1bear = possibleBalls(1,1) / possibleBalls(3,1);
ball1range = possibleBalls(2,1);
ball2bear = 0;
ball2range = 0;
ball3bear = 0;
ball3range = 0;



if (numBalls > 1)
    ball2bear = possibleBalls(1,2) / possibleBalls(3,2);
    ball2range = possibleBalls(2,2);
end
if (numBalls > 2)
    ball3bear = possibleBalls(1,3) / possibleBalls(3,3);
    ball3range = possibleBalls(2,3);
end
range = ball1range;
bear = ball1bear;
%disp([ball1bear,ball2bear,ball3bear]);
disp([range,bear]);
tennisBalls = [
     2,    28;
     2,    47;
     5,     2;
    11,    20;
    20,    13];

%disp(size(map));
for th = 1:size(pM,3)
    worldth = th * DTH;
    for x = 1:size(pM,1)
        for y = 1:size(pM,2)
            
            worldx = x * DX;
            worldy = y * DY;
            for ball = 1:size(tennisBalls,1)
                ballx = tennisBalls(ball,1) * DX;
                bally = tennisBalls(ball,2) * DY;
                angle = atan2(bally - worldy,ballx - worldx);
                if (abs(worldth - angle) < pi / 6)
                    % IN RANGE
                    fail = 0;
                    for lambda = 0:.09:1
                        scrutx = worldx * lambda + (1 - lambda) * ballx;
                        scruty = worldy * lambda + (1 - lambda) * bally;
                        discx = ceil(scrutx / DX);
                        discy = ceil(scruty / DY);
                        if (discx >= size(map,1) || discy >= size(map,2))
                            
                        elseif (map(discx,discy) == 1)
                            fail = 1;
                        end
                    end
                    if (fail == 0)
                        %disp([]);
                        pM(x,y,th) = pM(x,y,th);% + 0.1;%.3;
                        riseoverrun = sqrt((worldy - bally) ^ 2 + (worldx - ballx) ^ 2);
                        if(abs(angle-(bear + worldth)) < 0.09)
                            if(abs(riseoverrun - range) < 0.05) 
                                pM(x,y,th) = pM(x,y,th) * 1.0001 + 0.0000001;
%                            disp([ballx,bally]);
                              %  disp(angle);
                            end
                           % pM(x,y,th) = pM(x,y,th) * 1.0001 + 0.0000001;
                        else
                            pM(x,y,th) = pM(x,y,th) * (1-0.001*abs(angle-(bear + worldth)));% - (0.001*abs(riseoverrun - range));
                        end
                    else
                        %pM(x,y,th) = pM(x,y,th) - .005;
                    end
                end
            end
        end
    end
end

%to turn off observation model. 
%pM = oldPM;
%pM = smooth3(pM,'gaussian',5);
pause();
end