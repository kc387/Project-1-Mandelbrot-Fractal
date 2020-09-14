#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorOut.h"

/**************
**Translate pixel value given in MandelOut array into a color that can be found in the colorMap array
**Length of the MandelOut array = size * size
**Output should be written to outputfile with P3 format
***************/
int P3colorpalette(u_int64_t size, uint8_t** colorMap, int colorcount, u_int64_t * MandelOut, char* outputfile)
{
    //YOUR CODE HERE
    FILE* out = fopen(outputfile, "w");
    if(out == NULL) {
        return 1;
    }
    if(fprintf(out, "P3 %lu %lu %d\n", size, size, 255) < 0) {
        fclose(out);
        return 1;
    }
    for(int i = 0; i < size * size; i ++) {
        if(MandelOut[i] == 0) {
            fprintf(out, "%d %d %d\n", 0, 0, 0);
        }
        else if (MandelOut[i] > colorcount)
        {
            int index = MandelOut[i] % colorcount;
            if(index == 0) {
                int r = *(*(colorMap + colorcount - 1) + 0);
                int g = *(*(colorMap + colorcount - 1) + 1);
                int b = *(*(colorMap + colorcount - 1) + 2);
                fprintf(out, "%d %d %d\n", r, g, b);
            }
            else {
                int r = *(*(colorMap + index - 1) + 0);
                int g = *(*(colorMap + index - 1) + 1);
                int b = *(*(colorMap + index - 1) + 2);
                fprintf(out, "%d %d %d\n", r, g, b);
            }
        }
        else {
            int index = MandelOut[i];
            int r = *(*(colorMap + index - 1) + 0);
            int g = *(*(colorMap + index - 1) + 1);
            int b = *(*(colorMap + index - 1) + 2);
            fprintf(out, "%d %d %d\n", r, g, b);
        }
        
    }
    fclose(out);
    return 0;
}

/**************
**Same as above, but with P6 format
***************/
int P6colorpalette(u_int64_t size, uint8_t** colorMap, int colorcount, u_int64_t * MandelOut, char* outputfile)
{
    //YOUR CODE HERE
    FILE* out = fopen(outputfile, "w");
    if(out == NULL) {
        return 1;
    }
    if(fprintf(out, "P6 %lu %lu %d\n", size, size, 255) < 0) {
        fclose(out);
        return 1;
    }
    for(int i = 0; i < size * size; i ++) {
        if(MandelOut[i] == 0) {
            char rgb[] = {(char)0, (char)0, (char)0};
            fwrite(rgb, 1, 3, out);
        }
        else if (MandelOut[i] > colorcount)
        {
            int index = MandelOut[i] % colorcount;
            if(index == 0) {
                int r = *(*(colorMap + colorcount - 1) + 0);
                int g = *(*(colorMap + colorcount - 1) + 1);
                int b = *(*(colorMap + colorcount - 1) + 2);
                char rgb[] = {(char)r, (char)g, (char)b};
                fwrite(rgb, 1, 3, out);
            }
            else {
                int r = *(*(colorMap + index - 1) + 0);
                int g = *(*(colorMap + index - 1) + 1);
                int b = *(*(colorMap + index - 1) + 2);
                char rgb[] = {(char)r, (char)g, (char)b};
                fwrite(rgb, 1, 3, out);
            }
        }
        else {
            int index = MandelOut[i];
            int r = *(*(colorMap + index - 1) + 0);
            int g = *(*(colorMap + index - 1) + 1);
            int b = *(*(colorMap + index - 1) + 2);
            char rgb[] = {(char)r, (char)g, (char)b};
            fwrite(rgb, 1, 3, out);
        }
        
    }
    fclose(out);
    return 0;
} 