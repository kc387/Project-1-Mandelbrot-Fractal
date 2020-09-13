/*********************
**  Color Map generator
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function frees the memory allocated for colorMap.
**Length represents the number of elements in colorMap 
***************/
void freeMap(int length, uint8_t** colorMap)
{
    //YOUR CODE HERE 
}

/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
    //YOUR CODE HERE
    colorcount = 0;
    FILE* cfile = fopen('colorfile', 'r');
    if(cfile == NULL) {
        return NULL;
    }
    int numcount;
    if (fscanf(cfile, "%d", &numcount) != 1) {
        return NULL;
    }
    uint8_t** carray;
    uint8_t* rbg[3];
    uint8_t r, b, g;
    while(colorcount < numcount) {
        if (fscanf(cfile, "%hhu", "%hhu", "%hhu", r, b, g) != 3) {
            return NULL;
            }
        else {
            *rbg[0] = r;
            *rbg[1] = b;
            *rbg[2] = g;
            **carray = *rbg;
            carray++;
            colorcount++;
        }
    }
    return carray;
}


