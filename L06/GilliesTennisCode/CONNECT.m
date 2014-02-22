
url = 'http://192.168.1.107:8081/getCameraJpg';
ss = imread(url);
fh = image(ss);
while(1)
ss = imread(url);
set(fh,'CData',ss);
drawnow;
end