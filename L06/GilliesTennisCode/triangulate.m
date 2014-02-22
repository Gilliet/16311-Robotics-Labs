%width = 480, height = 640
%indexedCents goes (row,col), not xy
function [x,y,theta] = triangulate(indexedCents)
totalArea = 0;
totalLength = 0; 

%find the total area of the tennis balls and perimeter of the target
for x=1:1:4
    totalArea = totalArea + indexedCents(x,1);
    pieceLength = abs(indexedCents(x,2)-indexedCents(x,3));
    totalLength = totalLength + pieceLength;
end

%assumes a single tennis ball for now 

area = indexedCents(1,1);
xOffset = (indexedCents(1,3))-240;
yOffset = (640-indexedCents(1,2))-320;


%fprintf('x: %f2, y: %f2\n',indexedCents(1,3),indexedCents(1,2));

x = 0; 
y = 0;
theta = 0;
%fprintf('area: %f2, xOffset: %f2, yOffset: %f2\n',area,xOffset,yOffset);

for z = 1:1:4
    asdf = indexedCents(z,1);
    if (asdf > 1)
        fprintf('x: %f2, y: %f2, area: %f2\n',indexedCents(z,3),indexedCents(z,2),indexedCents(z,1));
        y = indexedCents(z,2);
        xOut = 0.0085*(exp(0.0471*y)); %whatever, fine for now
        x = indexedCents(z,3);
        yOut = (0.0645*x)-15.918;
        theta = atan2(yOut,xOut);
        fprintf('x out: %f2, y out: %f2 theta out: %f2\n',xOut,yOut,theta*(180.0/3.14159265));
    end
end

