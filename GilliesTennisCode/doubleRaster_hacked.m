function [ drast, cntr ] = doubleRaster_hacked(img,H,W)
img_in = img;

%%RASTERING
cntr = 0;
%cntr is the number of spots found
matches = zeros(1,2);
%matches is a list of which areas are next to each other
for x=1:1:H
    for y=1:1:W
        if (img(x,y) > 0)
            up = 0;
            if (y > 1) up = img(x,y-1); end
            left = 0; 
            if (x > 1) left = img(x-1,y); end
            
            %start checking for neighbors
            if ((up == 0) && (left == 0))
                cntr = cntr + 1;
                img(x,y) = cntr;
                
            elseif ((left > 0) && (up > 0))
                img(x,y) = min(up, left);
                %set pixel and note match in matches
                [~,indx] = ismember([up,left],matches,'rows');
                if ((left ~= up) && (indx == 0))
                matches(size(matches,1)+1,1) = up;
                matches(size(matches,1),2) = left;

                end
            else
                img(x,y) = up+left; %since one of them will be 0
            end
        end
    end
end


%%UNION FIND: use matches as our edge list to find connected components in
%the 'graph' of found spots. 

%make an array of length cntr with each elem as itself to start
arry = ones(cntr); 
for w=1:1:cntr
   arry(w) = w; 
end

%now union find! 
for w=1:1:size(matches)
    mx = max(matches(w,1),matches(w,2));
    mn = min(matches(w,1),matches(w,2));
    if ((mx ~= 0) && (mn ~= 0))
        arry(mx) = arry(mn);
    end
end

%%RECTIFY the old spot list- now we know which ones are in the same 
% connected component
cntr2 = 0;
for z=1:1:H
    for z2=1:1:W
        oldi = img(z,z2);
        if (oldi == 0)
            actual = 0;
        else
            actual = arry(img(z,z2));
        end
        img(z,z2) = actual;
        cntr2 = max(cntr2,actual);
    end
end

drast = img;
