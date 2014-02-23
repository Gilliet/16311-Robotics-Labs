
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
disp([xsize,ysize,tsize]);
for th = 1:tsize
    worldth = th * DTH;
    wrapth = worldth + dth;
        if (wrapth > 2 * pi)
            wrapth = wrapth - 2 * pi;
        elseif (wrapth < .1)
            wrapth = wrapth + 2 * pi;
        end
    newth = ceil((wrapth) / DTH);
    for x = 1:xsize
        for y = 1:ysize
            worldx = x * DX;
            worldy = y * DY;
            mat = [cos(worldth), -sin(worldth), worldx;
                   sin(worldth), cos(worldth),  worldy;
                   0       ,      0,  1];
            pose = [dx;dy;1];
            newpose = mat * pose;
            newx = ceil((newpose(1)) / DX);
            newy = ceil((newpose(2)) / DY);
            if (newth > 0 && newx > 0 && newy > 0 && newth <= tsize && newx <= xsize && newy <= ysize)
%                disp([newx,newy,newth]);
                newPM(x ,y,th) = pM(newx,newy,newth);
%                disp([newx,newy,newth]);
            else
            end
            
            
        end
    end
end


outPM = newPM;


%first, shift

%second, blur
%make gaussian: make 3 1-d gaussians and convolve it with each of them? :(
%how big do i make each 1-d gaussian? i guess as big as the dimension
end
