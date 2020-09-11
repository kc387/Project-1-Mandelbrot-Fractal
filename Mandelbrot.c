#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * c, double threshold)
{
    //YOUR CODE HERE
    u_int64_t iters = 0;
    ComplexNumber* z = newComplexNumber(0, 0);
    while (iters < maxiters) {
        ComplexNumber* m = newComplexNumber(0, 0);
        m = ComplexProduct(ComplexProduct(z, z), c);
        if (ComplexAbs(m) > threshold) {
            return iters;
        }
        iters++;
        z = m;
    }
    return 0;
} 

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    //YOUR CODE HERE
}


