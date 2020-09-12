#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>
#include <math.h>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * c, double threshold)
{
    //YOUR CODE HERE
    u_int64_t iters = 0;
    ComplexNumber* z = newComplexNumber(0, 0);
    ComplexNumber* m = newComplexNumber(0, 0);
    while (iters < maxiters) {
        ComplexNumber* z_2 = ComplexProduct(z, z);
        m = ComplexSum(z_2, c);
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
    u_int64_t size = pow((2 * resolution + 1), 2);
    output [size];
    ComplexNumber* c = newComplexNumber(0, 0);
    for (int i = 0; i < size; i += 1) {
        double r = -scale + i%(2*resolution+1) * (scale/resolution);
        int q = i/(2*resolution+1);
        double col = -scale + q * (scale/resolution);
        ComplexNumber* inside = newComplexNumber(r, col);
        c = ComplexSum(center, inside);
        u_int64_t mandelbrot = MandelbrotIterations(max_iterations, c, threshold);
        output[i] = mandelbrot;
    }
}


