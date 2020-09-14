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
    for(int i = 0; i < length; i ++) {
        free(*(colorMap + i));
    }
    free(colorMap);
}

/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
    //YOUR CODE HERE
    FILE* cfile = fopen(colorfile, "r");
    if(cfile == NULL) {
        return NULL;
    }
    if (fscanf(cfile, "%d", colorcount) != 1) {
        return NULL;
    }

    uint8_t** carray = (uint8_t**) malloc (*colorcount * sizeof(uint8_t*));
    int r, g, b;
    for(int i = 0; i < *colorcount; i++) {
        if (fscanf(cfile, "%d %d %d", &r, &g, &b) != 3) {
            return NULL;
            }
        else {
            if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0) {
                freeMap(i + 1, carray);
                return NULL;
            }
            uint8_t* rgb = (uint8_t*) malloc (3 * sizeof(uint8_t));
            rgb[0] = (uint8_t)r;
            rgb[1] = (uint8_t)g;
            rgb[2] = (uint8_t)b;
            carray[i] = rgb;
            free(rgb);
        }
    }
    fclose(cfile);
    return carray;
}


