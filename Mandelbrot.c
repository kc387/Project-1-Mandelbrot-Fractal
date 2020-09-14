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
    ComplexNumber* z = newComplexNumber(0.0, 0.0);
    while (iters < maxiters) {
        if (ComplexAbs(z) > threshold) {
            return iters;
        }
        freeComplexNumber(z);
        ComplexNumber* z_2 = ComplexProduct(z, z);
        z = ComplexSum(z_2, c);
        freeComplexNumber(z_2);
        iters++;
    }
    freeComplexNumber(z);
    return 0;
} 

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    //YOUR CODE HERE
    //u_int64_t size = (2 * resolution + 1) * (2 * resolution + 1);
    //output [size];
    for (int i = 0; i < 2*resolution+1; i ++) {
        for(int j = 0; j < 2*resolution+1; j++) {
            ComplexNumber* inside = newComplexNumber(-scale + j*(scale/(double)resolution), scale - i*(scale/(double)resolution));
            ComplexNumber* c = ComplexSum(center, inside);
            if(inside != NULL && c != NULL) {
                *output = MandelbrotIterations(max_iterations, c, threshold);
                output ++;
                free(c);
                free(inside);
            }
        }
    }
}


