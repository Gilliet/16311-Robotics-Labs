%heuristic for triangulating from smaller target
function [dist,error] = littleTriangulate(len,area)

da = (188758/area).^(1/1.598);%area
dl = (-51.725)+(1.58983)*sqrt((-1.258)*len + 2578.19);%length
error = abs(da-dl);
dist = (da+dl)/2;
