function [uh] = triangulate(indexedCents)
totalArea = 0;
totalLength = 0; 

%find the total area of the tennis balls and perimeter of the target
for x=1:1:4
    totalArea = totalArea + indexedCents(x,1);
    pieceLength = abs(indexedCents(x,2)-indexedCents(x,3));
    totalLength = totalLength + pieceLength;
end

%try the big and little triangulations and keep the measurement that 
%had the least error
[db,errb] = bigTriangulate(totalLength,totalArea);
[dl,errl] = littleTriangulate(totalLength,totalArea);

if (errb < errl)
    uh = db;
else
    uh = dl;
end
fprintf('depth: %f5 \n',uh);

