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
    free(colorMap);
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
    else{
        fscanf(cfile, "%d", &numcount);
    }

    uint8_t** carray = (uint8_t**) malloc (sizeof(uint8_t*));
    uint8_t* rbg[3];
    uint8_t r, b, g;
    while(colorcount < numcount) {
        if (fscanf(cfile, "%hhu", "%hhu", "%hhu", r, b, g) != 3) {
            return NULL;
            }
        else {
            uint8_t* carray = (uint8_t*) malloc (3 * sizeof(uint8_t));
            *rbg[0] = r;
            *rbg[1] = b;
            *rbg[2] = g;
            *carray = rbg;
            carray++;
            colorcount++;
        }
    }
    fclose(cfile);
    return carray;
}


