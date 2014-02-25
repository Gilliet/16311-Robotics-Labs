
%pM is the initial probability map, dPose is the change in pose from your
%measurement 
function [outPM] = transitionModel(pM,dPose)
global DX;
global DY;
global DTH;
%TODO implement this part to update pM based on the instrument 
%1. scale newPM in the directions indicated by dPose
%2. blur the resulting pm by a factor of dPose

xsize = size(pM,1);
ysize = size(pM,2);
tsize = size(pM,3);
newPM = (ones(xsize,ysize,tsize))*(min(pM(:)));

%dPose

dx = dPose(1);
dy = dPose(2);
dth = dPose(3);

for th = 1:tsize
    worldth = th * DTH; %% Translate to world coordinates
    wrapth = wrapTo2Pi(worldth + dth); %% Increment and wrap the theta value.
    newth = round((wrapth) / DTH); %% Translate the new theta value back to coordinate frame.
    mat = [cos(wrapth), -sin(wrapth), 0;
          sin(wrapth), cos(wrapth), 0;
                   0       ,      0,  1];
    transpose = -[dx;dy;1]; %% Rotate the delta x and y to world frame.
    worlddx = transpose(1);
    worlddy = transpose(2);
    for x = 1:xsize
        for y = 1:ysize
            newx = round((x * DX + worlddx) / DX); %% Compute the new x and y values.
            newy = round((y * DY + worlddy) / DY);
            if (newth > 0 && newx > 0 && newy > 0 && newth <= tsize && newx <= xsize && newy <= ysize)
                 %newPM(x,y,th) = pM(newx,newy,newth);
                 newPM(newx,newy,th) = pM(x,y,newth);
            end
        end
    end
end

%disp(dPose);
outPM = newPM;
%outPM = pM;

%first, shift

%second, blur
%make gaussian: make 3 1-d gaussians and convolve it with each of them? :(
%how big do i make each 1-d gaussian? i guess as big as the dimension

smooth3(outPM,'gaussian',9,2);
end
