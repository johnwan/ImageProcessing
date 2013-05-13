upresult-neighbor.pgm is the up sampling result made by Nearest neighbor algorithm.

upresult-bilinear.pgm is the up sampling result made by Bilinear interpolation(Four point) algorithm.

I occured a problem is that when the Bilinear interpolation closed to the edge, it can't find all the four point,
therefore I copy the nearest neighbor's value to them. I think less than 3 rows or cols will not make a big 
different.
