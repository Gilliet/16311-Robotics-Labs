%%gives areas of the blobs in the image! also does some filtering to 
%identify the actual "blobs" vs. noise, returning the four largest. 

function [areas,indexedBiggest] = findAreas(img,cntr,H,W)
areas0 = zeros(cntr);
totalArea = 0;
twothous = 2000*(ones(cntr,1));
zs = zeros(cntr,1);
%span keeps track of the top-,bottom-,left-, and right-most pixels of a blob
span = [twothous,zs,twothous,zs];
%baselines to (easily) beat. top bottom left right

for x=1:1:H
    for y=1:1:W
        if (img(x,y) ~= 0)
           areas0(img(x,y)) = areas0(img(x,y))+1;
           totalArea = totalArea+1;
           %update total area and area of that spot, plus blob's edges
           if(x < span(img(x,y),1))
                span(img(x,y),1) = x; 
           end
           if(x > span(img(x,y),2))
                span(img(x,y),2) = x; 
           end
           if(y < span(img(x,y),3))
                span(img(x,y),3) = y; 
           end
           if(y > span(img(x,y),4))
                span(img(x,y),4) = y; 
           end
        end
    end
end

areas = areas0; %keep the old guys around for now

%take out the ones that are too long/wide
for x=1:1:size(span,1)
    if((span(x,2)-span(x,1)) > 1.75*(span(x,4)-span(x,3)))
        areas(x) = 0;
    end
    if((span(x,4)-span(x,3)) > 2*(span(x,2)-span(x,1)))
        areas(x) = 0;
    end
end

%%now clear out littler blobs, leaving and returning the four largest blobs
fourBiggest = [0 0 0 0];
evict = [0 0 0 0];

for x=1:1:size(areas)
        if (areas(x) > fourBiggest(1))
            fourBiggest(1) = areas(x);
            evict(1) = x;
        end   
end
if (evict(1) ~= 0) 
    areas(evict(1)) = -1;
end

for x=1:1:size(areas)
        if (areas(x) > fourBiggest(2))
            fourBiggest(2) = areas(x);
            evict(2) = x;
        end    
end
if (evict(2) ~= 0) 
    areas(evict(2)) = -2;
end

for x=1:1:size(areas)
        if (areas(x) > fourBiggest(3))
            fourBiggest(3) = areas(x);
            evict(3) = x;
        end   
end
if (evict(3) ~= 0) 
    areas(evict(3)) = -3;
end

for x=1:1:size(areas)
        if (areas(x) > fourBiggest(4))
            fourBiggest(4) = areas(x);
            evict(4) = x;
        end    
end
if (evict(4) ~= 0) 
    areas(evict(4)) = -4;
end

for x=1:1:size(areas)
        if(areas(x) >= 0)
            areas(x) = 0;
        else
            for y=1:1:4
                if (evict(y) == x)
                    areas(x) = fourBiggest(y);
                end
            end
        end
end

indexedBiggest = zeros(4,2);
for x=1:1:4
    indexedBiggest(x,1) = fourBiggest(x);
    indexedBiggest(x,2) = evict(x);
end

%if it's too small, just zero it out
avgSize = (fourBiggest(1)+fourBiggest(2)+fourBiggest(3)+fourBiggest(4))/4;

for x=1:1:4
    if (indexedBiggest(x,1) < 0.5*avgSize)
        indexedBiggest(x,1) = 0;
        areas(x) = 0;
        %fprintf('evicting\n');
    end 
    
end

end



