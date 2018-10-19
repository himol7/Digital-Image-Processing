
img1 = double(imread('twoboats.jpg'))/255;
img2 = double(imread('lenna.jpg'))/255;

[rows1, cols1] = size(img1);
[rows2, cols2] = size(img2);

rows = max(rows1, rows2);
cols = max(cols1, cols2);

fft1 = fft2(img1, rows, cols);
fft2 = fft2(img2, rows, cols);

mag1 = abs(fft1);
mag2 = abs(fft2);
pha1 = angle(fft1);
pha2 = angle(fft2);

inv1 = mag2 .* exp(j*pha1);
inv2 = mag1 .* exp(j*pha2);

inv1 = real(ifft2(inv1));
inv2 = real(ifft2(inv2));

figure;
imshow(inv1, []);
figure;
imshow(inv2, []);
