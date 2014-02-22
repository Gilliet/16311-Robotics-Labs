%heuristic for triangulating from bigger target
function [dist,error] = bigTriangulate(len,area)

da = (280524/area).^(1/1.62);%area
dl = (-2.8426*(10.^(-9)))*(len.^3)+(1.92794*(10.^(-5)))*(len.^2) ...
         -0.044075686*len+36.2623388;%length

error = abs(da-dl);
dist = (da+dl)/2;
