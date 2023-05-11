a = imread('lena_ori.gif');
imshow (a);
[ pixelCount grayLevels ] = imhist(a,256);
z = [grayLevels pixelCount];
allpixel = sum(z(:,2)) ;
Probability = z(:,2)/allpixel;
z = [z Probability];
