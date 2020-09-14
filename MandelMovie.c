#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include "ColorMapInput.h"
#include "ColorOut.h"
#include <sys/types.h>
 
void printUsage(char* argv[])
{
    printf("Usage: %s <threshold> <maxiterations> <center_real> <center_imaginary> <initialscale> <finalscale> <framecount> <resolution> <output_folder> <colorfile>\n", argv[0]);
    printf("    This program simulates the Mandelbrot Fractal, and creates an iteration map of the given center, scale, and resolution, then saves it in output_file\n");
}


/*
This function calculates the threshold values of every spot on a sequence of frames. The center stays the same throughout the zoom. First frame is at initialscale, and last frame is at finalscale scale.
The remaining frames form a geometric sequence of scales, so 
if initialscale=1024, finalscale=1, framecount=11, then your frames will have scales of 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1.
As another example, if initialscale=10, finalscale=0.01, framecount=5, then your frames will have scale 10, 10 * (0.01/10)^(1/4), 10 * (0.01/10)^(2/4), 10 * (0.01/10)^(3/4), 0.01 .
*/
void MandelMovie(double threshold, u_int64_t max_iterations, ComplexNumber* center, double initialscale, double finalscale, int framecount, u_int64_t resolution, u_int64_t ** output){
    double mul = pow((finalscale/initialscale), 1.0/(framecount-1));
    double scale = initialscale;
    for(int i = 0; i < framecount; i++){
    	Mandelbrot(threshold, max_iterations, center, scale, resolution, output[i]);
    	scale *= mul;

    }
}

/**************
**This main function converts command line inputs into the format needed to run MandelMovie.
**It then uses the color array from FileToColorMap to create PPM images for each frame, and stores it in output_folder
***************/
int main(int argc, char* argv[])
{
    //Tips on how to get started on main function: 
    //MandelFrame also follows a similar sequence of steps; it may be useful to reference that.
    //Make sure you complete the steps below in order. 

    //STEP 1: Convert command line inputs to local variables, and ensure that inputs are valid.
    /*
    Check the spec for examples of invalid inputs.
    Remember to process the colorfile.
    */

    //YOUR CODE HERE 
    if(argc != 11) {
        printf("Main Error \n");
        return 1;
    }

    double threshold, initialscale, finalscale;
    int framecount;
    ComplexNumber* center;
    u_int64_t max_iterations, resolution;
    u_int64_t ** output;
    char * output_folder;
    char * colorfile;

    threshold = atof(argv[1]);
    max_iterations = (u_int64_t)atoi(argv[2]);
    center = newComplexNumber(atof(argv[3]), atof(argv[4]));
    initialscale = atof(argv[5]);
    finalscale = atof(argv[6]);
    framecount = atoi(argv[7]);
    resolution = (u_int64_t)atoi(argv[8]);
    output_folder = argv[9];
    colorfile = argv[10];

    if (threshold <= 0 || initialscale <= 0 || finalscale <= 0 || max_iterations <= 0 || framecount <= 0 || framecount > 10000) {
    	printf("Main Error \n");
    	freeComplexNumber(center);
    	return 1;
    }

    if(framecount == 1 && initialscale != finalscale) {
        printf("Main Error \n");
    	freeComplexNumber(center);
    	return 1;
    }

    u_int64_t size = 2 * resolution + 1;

    int colorcount;
    uint8_t** colormap = FileToColorMap(colorfile, &colorcount);

    //STEP 2: Run MandelMovie on the correct arguments.
    /*
    MandelMovie requires an output array, so make sure you allocate the proper amount of space. 
    If allocation fails, free all the space you have already allocated (including colormap), then return with exit code 1.
    */

    //YOUR CODE HERE 
    output = (uint64_t **) malloc (framecount * sizeof(uint64_t*));

    if(output == NULL) {
        printf("Main Error \n");
        freeComplexNumber(center);
        free(output);
        freeMap(colorcount, colormap);
    	return 1;
    }

    for (int i = 0; i < framecount; i ++) {
        *(output + i) = (uint64_t *) malloc (size * size * sizeof(uint64_t));
        if(*(output + i) == NULL) {
            printf("Main Error \n");
            freeComplexNumber(center);
            for(int j = 0; j < i; j++) {
                free(*(output + j));
            }
            free(output);
            freeMap(colorcount, colormap);
            return 1;
        }
    }

    if(colormap == NULL) {
        printf("Main Error \n");
        return 1;
    }

    MandelMovie(threshold, max_iterations, center, initialscale, finalscale, framecount, resolution, output);

    //STEP 3: Output the results of MandelMovie to .ppm files.
    /*
    Convert from iteration count to colors, and output the results into output files.
    Use what we showed you in Part B.1.2, create a seqeunce of ppm files in the output folder.
    Feel free to create your own helper function to complete this step.
    As a reminder, we are using P6 format, not P3.
    */

    //YOUR CODE HERE 
    FILE* outputfile = fopen(argv[9], "w+");
    for (int i = 0; i < framecount; i ++) {
        char* b = (char*) malloc (100 * sizeof(char));
        sprintf(b, "%s/frame%05d.ppm", output_folder, i);
        P6colorpalette(size, colormap, colorcount, output[i], b);
        free(b);
    }

    fclose(outputfile);


    //STEP 4: Free all allocated memory
    /*
    Make sure there's no memory leak.
    */
    //YOUR CODE HERE 
    freeMap(colorcount, colormap);
    freeComplexNumber(center);
    for(int i = 0; i < size*size; i ++) {
        free(*(output + i));
    }
    free(output);

    return 0;
}

