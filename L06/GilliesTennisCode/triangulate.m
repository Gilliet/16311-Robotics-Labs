%width = 480, height = 640
%indexedCents goes (row,col), not xy
function [orientations] = triangulate(indexedCents)

orientations = zeros(4,3);

%fprintf('area: %f2, xOffset: %f2, yOffset: %f2\n',area,xOffset,yOffset);

for z = 1:1:4
    asdf = indexedCents(z,1);
    if (asdf > 1)
        %fprintf('x: %f2, y: %f2, area: %f2\n',indexedCents(z,3),indexedCents(z,2),indexedCents(z,1));
        y = indexedCents(z,2);
        xOut = 0.0085*(exp(0.0471*y)); %whatever, fine for now
        x = indexedCents(z,3);
        yOut = (0.0645*x)-15.918;
        theta = atan2(yOut,xOut);
        %fprintf('x out: %f2, y out: %f2 theta out: %f2\n\n',xOut,yOut,theta*(180.0/3.14159265));
        orientations(z,1) = xOut;
        orientations(z,2) = yOut;
        orientations(z,3) = theta;
    end
end

