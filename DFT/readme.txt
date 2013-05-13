Thx god!! I did it!!

I found just rescale the image is not the fundamental problem, I changed the formula to make the result we get 
can be more accurate.

// here is the formula in the hint document
            x2[m*i+j] += (x1[m*i+k] * cosarg);
            y2[m*i+j] += (-x1[m*i+k] * sinarg);
// here is the formula of original transfor equation
            x2[m*i+j] += (x1[m*i+k] * cosarg - y1[m*i+k] * sinarg);
            y2[m*i+j] += (x1[m*i+k] * sinarg + y1[m*i+k] * cosarg);



If I do not change the formula even when d0=320, fmax = 184 fmin = -124.5, therefore if I did the rescaling, the 
image contrast will be worse. 

After changing the formula to that, the images seems much better than before. However, rescale still necessary 
when d0 is small.
d0 = 320  fmax = 255        fmin = -0.000001
d0 = 50   fmax = 245.807083 fmin = -71.922607

d0 = 50.pgm , d0 = 160.pmg , d0 = 320.pgm are the three images with different cutoff frequencies.
d0 = 320 with old formula.pgm is a comparing image with the new version.

DFT.dev is the project file.
inout.c edgemag.c is the c file you gave to us, I didn't change anything.
main.c is the main program, I left comment in most of place I changed.
DFT.c is the file to process DFT and IDFT. dir is the value control it is DFT or IDFT, m,n are cols and rows of 
the image, *x1,*y1 is the real and image part of the matrix.

I think I understand DFT more clearly. Thank you Sir~