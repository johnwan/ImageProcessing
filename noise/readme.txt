noise.dev --- Project File
noise.exe --- main .exe file

Uniform Noise:

a = 30;
b = 60;

Salt-and-Pepper Noise:

a = 30; Pa= 0.01;
b = 60; Pb= 0.01;


There have some problem.
1.Histogram is too high to display, so we need to compress the height of the histogram to 256.

Here I found two method:
1. Take the square root.

sqar-ImpulseNoiseResult.pgm --- Image with Impulse Noise
sqar-ImpulseNoiseHisto.pgm --- Histogram of Image with Impulse Noise

sqar-UniformNoiseResult.pgm --- Image with Uniform Noise
sqar-UniformNoiseHisto.pgm --- Histogram of Image with Uniform Noise

2. use the formula 255*histo[i]/max, I believe this one looks better.

ImpulseNoiseResult.pgm --- Image with Impulse Noise
ImpulseNoiseHisto.pgm --- Histogram of Image with Impulse Noise

UniformNoiseResult.pgm --- Image with Uniform Noise
UniformNoiseHisto.pgm --- Histogram of Image with Uniform Noise



2.I searched in the Internet and found some of the Salt-and-Pepper Noise Generator just use the noise to replace 
the orginal image, this way can generate some noise darker than 100 in the circle, it looks similar as the image
of your Slides, and more like the "Salt and Pepper".
Therefore I generate another image of Salt-and-Pepper with this method.

replace-ImpulseNoiseResult.pgm --- Image with Impulse Noise
replace-ImpulseNoiseHisto.pgm --- Histogram of Image with Impulse Noise

