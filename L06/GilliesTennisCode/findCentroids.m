%%Finds centroids of the image's four biggest blobs, as indicated by 
%indexedSizes
function [cents,indexedCents] = findCentroids(img,areas,indexedSizes,cntr,H,W)
cents = zeros(cntr,2);
%cents = centroids of the image
for x=1:1:H
    for y=1:1:W
        if (img(x,y) ~= 0)
           %add up indices for each blob
           cents(img(x,y),1) = cents(img(x,y),1)+ x;         
           cents(img(x,y),2) = cents(img(x,y),2)+ y;
        end
    end
end

%largest centroids indexed the same way as they were in indexedSizes
indexedCents = zeros(4,1,1);

for x=1:1:cntr
    if (areas(x) ~= 0)
        %divide to get average center point
        cents(x,1) = cents(x,1)*(1/areas(x));
        cents(x,2) = cents(x,2)*(1/areas(x));
        for y=1:1:4
        if(indexedSizes(y,1) == areas(x))
            indexedCents(y,1) = areas(x);
            indexedCents(y,2) = cents(x,1);
            indexedCents(y,3) = cents(x,2);
          
        end
        end
    else
        cents(x,1) = 0;
        cents(x,2) = 0;
    end
end

%now take out ones that are too high up
for x=1:1:4
    if (indexedCents(x,2) > 0.4*(640))
    %    indx = indexedCents(x,1)
    %cents(indx) = 0;
    indexedCents(x,1) = 0;
    indexedCents(x,2) = 0;
    indexedCents(x,3) = 0;
    end
end



