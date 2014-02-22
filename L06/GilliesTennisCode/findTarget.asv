% 16-311 Lab 02 Framework
% 
% Gillian Rosen, gtr
% Original HW2 framework written by Humphrey Hu, humhu@cmu.edu
% 
% 1/16/2014

function [] = findTarget(image_path)%, output_path)
%fprintf('image path: %s\n',image_path);
% FINDTARGET - Finds the tennis ball targets! 
% Usage:
% findTarget(image_path, output_path) - Finds targets in an image specified by
% image_path and saves to a log specified by output_path.

%% 1. Image Basics
% Image files can be read with imread(). Here we read Waldo in PNG format
% to get a RGB (N X M X 3) matrix, where the 3rd dimensions are the RGB
% channels, respectively
in_rgb = imread(image_path);
fprintf('Loaded in as a %d by %d by %d matrix.\n', ...
    size(in_rgb,1), size(in_rgb,2), size(in_rgb,3));


% Convert the RGB matrix to HSV, with values 0 to 255
% Note: imread and rgb2hsv return matrices of uint_8
% Calling double() converts these to doubles, which are easier to use
%note: later, use rgb2grayscale to get a 2d matrix of the things
in_hsv = double(rgb2hsv(in_rgb));

H = size(in_hsv, 1); W = size(in_hsv, 2); % Get image height and width


%% 2. Find Tennis balls! 

%first, threshold
thresh = double(zeros(H,W));
for x=1:1:H
    for y=1:1:W   %get bright yellow-green pixels 
        if((in_hsv(x,y,1) > 43/255) && (in_hsv(x,y,1) < 55/255) ...
            && (in_hsv(x,y,2) > 70/255) && (in_hsv(x,y,2) < 225/255) ...
            && (in_hsv(x,y,3) > 65/255) && (in_hsv(x,y,3) < 250/255))
            thresh(x,y) = 1.0;
        end
    end
end

%prepare to write all image files
strt = length(image_path)-6;
en = length(image_path)-4;
whichIm =image_path(strt:en); 
whichIm = strcat(whichIm,'.png');
%write threshed image file
threshname = strcat('intermed/thresh',whichIm);
%imwrite(thresh,threshname);
%figure;
%imshow((thresh));
%title('threshed');

%now clean it up! dilate to make blobs cohere, then erode
SEE0 = strel('disk',4,4);
e0 = imerode(thresh,SEE0);

SED = strel('disk',28,4);
dil = imdilate(e0,SED);

SEE = strel('disk',17,4);
erod = imerode(dil,SEE);

%write cleaned image file
cleanname = strcat('intermed/clean',whichIm);
%imwrite(erod,cleanname);
%figure;
%imshow((erod));
%title('eroded.')

%next, do segmentation- double raster segmentation as described in class
rs = erod; 
[ rs,cntr ] = doubleRaster_hacked(rs,H,W); 

visRaster = in_hsv;
visRaster(:,:,1) = rs/255;
visRaster(:,:,2) = ones(H,W);
visRaster(:,:,3) = erod;

%write segmented image file
segname = strcat('intermed/segmented',whichIm);
%imwrite(hsv2rgb(visRaster),segname);
%figure;
%imshow(hsv2rgb(visRaster));
%title('segmented');

%cntr
[areas,indexedSizes] = findAreas(rs,cntr,H,W);
%indexedSizes
%areas
[cents,indexedCents] = findCentroids(rs,areas,indexedSizes,cntr,H,W);
%indexedCents
%cents
%indexedSizes and indexedCents are aligned, with the blob of size i at i,1 
%     in both. indexedSizes also stores its counter number, and
%     indexedCents also stores its centroid. 

%uh gives the distance from the target, as specified by the centroids
%and areas in indexedCents
[x,y,theta] = triangulate(indexedCents);

%visualize the centroids
visCentroids = in_hsv;
visCentroids(:,:,1) = rs/20;
visCentroids(:,:,2) = ones(H,W);
visCentroids(:,:,3) = erod;
for x=1:1:4
        if(indexedCents(x,1) ~= 0)
            o = 0.08;
            b = 0.65;
            temp1 = int32(indexedCents(x,2));
            temp2 = int32(indexedCents(x,3)); 
            
            for y=0:1:6
                visCentroids(temp1,temp2,1) = o;
                visCentroids(temp1+y,temp2,1) = o;
                visCentroids(temp1-y,temp2,1) = o;
                visCentroids(temp1,temp2+y,1) = o;
                visCentroids(temp1,temp2-y,1) = o;
                
            visCentroids(temp1+1,temp2+y,1) = b;
            visCentroids(temp1+1,temp2-y,1) = b;
            visCentroids(temp1-1,temp2+y,1) = b;
            visCentroids(temp1-1,temp2-y,1) = b;
                
            visCentroids(temp1+y,temp2+1,1) = b;
            visCentroids(temp1+y,temp2-1,1) = b;
            visCentroids(temp1-y,temp2+1,1) = b;
            visCentroids(temp1-y,temp2-1,1) = b;
            end
        end
end

%write the centroids image file
centsname = strcat('intermed/cents',whichIm);
figure;
imshow(hsv2rgb(visCentroids));
%imwrite(hsv2rgb(visCentroids),centsname);

%% 3. File I/O

% First we open a file and get a file ID # with fopen(). 'w' specifies we
% want to write.
%output_path = 'distances.txt';
%file_id = fopen(output_path, 'a+');
%if file_id == -1    % -1 is an invalid file ID and signals failure
%    fprintf('File creation failed!\n');
%    return;
%end

% Now we can write to the file using fprintf (formatted print to file)
% fprintf uses a format specifier string, where %d represents an integer
% and %f represents a floating point number. You can then give fprintf the 
% value you want to substitute into the string as additional arguments.
%'\n' is the special character for newline (or the enter key), and '/t' 
% is the tab character.

% If the file ID # is given to fprintf, it will write into the file instead
% of the terminal.

%write distances to file
%fprintf(file_id, 'distance from camera in %s: %f5 feet\r\n',whichIm,uh);

% Finally when you're done, you should close the file with fclose()
%fclose(file_id);
