#ifndef TP1_H_
#define TP1_H_

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

typedef struct mandel_pic
{
    int width;
    int height;
    double Xmin;
    double Ymin;
    double scale;
    double pixwidth;
    int *convrg;
} mandel_pic_t;




#endif /* !TP1_H_ */
