%pM stands for probability map, map is the input map showing where obstacles
%and tennis balls are located, measurement is the reading from the sensor
%pipeline. In the simulator case this is a n by 2 matrix where the first
%column is the bearing to an observed tennis ball and the second column is
%the range to a observed tennis ball. 
function [pM] = observationModel(map,measurement,pM)
global DX;        %discretization along x axis
global DY;       %discretization along y axis
global DTH;      %discretization along th
tennisBalls = [
     2,29;
     2,47;
    10,23;
    11,8;
    18,4;
    20,20];


disp(measurement);


%TODO given the measurement, map, and current probability map update the
%probability map 

%step 1: take noise out of measurements @_@ 
%specifically, the measurements seem to be a very noisy picture
% of just one or two tennis balls
oldPM = pM;
newPM = ones(size(pM,1),size(pM,2),size(pM,3)) * (min(pM(:)));
xsize = size(pM,1);
ysize = size(pM,2);
tsize = size(pM,3);
ptimes = 1.01;
pinc = 0.00001;

for ball = (1:size(tennisBalls,1))
    for i = (1:size(measurement,1))
        bearing = measurement(i,1);
        range = measurement(i,2);
        ballx = tennisBalls(ball,1) * DX;
        bally = tennisBalls(ball,2) * DY;
        for angle = 0:.2:2*pi
            candx = ballx + cos(angle) * range;
            candy = bally + sin(angle) * range;
            w = pi/2 - atan2(candy - bally, candx - ballx);
            candth = pi / 2 + w - bearing;
            discx = round(candx / DX);
            discy = round(candy / DY);
            discth = round(candth / DTH);
            fail = 0;
            for lam = 0:0.09:1
                scrutx = round((lam * candx + (1-lam) * ballx)/DX);
                scruty = round((lam * candy + (1-lam) * bally)/DY);
                if (scrutx > 0 && scruty > 0 && scrutx < xsize && scruty < ysize && map(scrutx,scruty) == 1)
                    fail = 1;

                end
            end
            if (fail == 0)
            %    disp('good candidate');
            end
            if (fail ~= 1 && discx > 0 && discy > 0 && discth > 0 && discx < xsize && discy < ysize && discth < tsize)
                newPM(discx,discy,discth) = pM(discx,discy,discth) * ptimes;
              %  disp('found a thing');
             %   pause();
            end
        end
    end
end
pM = pM .* smooth3(newPM,'gaussian',9);
%pM = oldPM;
end

