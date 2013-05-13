I wrote down sampling with Nearest neighbor and Bilinear interpolation, 
downresult-neighbor.pgm shows the down sampling result made by Nearest neighbor algorithm.
downresult-average.pgm shows the down sampling result made by average value algorithm.
I found the problem was that I forgot let sum=0 after one cycle, it let sum out of range.