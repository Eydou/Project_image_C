#ifndef TP3_H_
#define TP3_H_

#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct color
{
    char red;
    char green;
    char blue;
} color_t;


typedef struct picture
{
    int width;
    int height;
    struct color* pixels;
}picture_t;


#endif /* !TP3_H_ */
