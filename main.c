#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <complex.h>

struct color
{
  char red;
  char green;
  char blue;
};

struct color palette(int c)
{
  struct color color;
  while (c > 1785)
  {
    c -= 1275;
  }
  if (c >= 0 && c <= 255){
    color.red = c;
    color.green = 0;
    color.blue = 0;
  }
  if (c > 255 && c <= 510){
    color.red = 255;
    color.green = c - 255;
    color.blue = 0;
  }
  if (c > 510 && c <= 765){
    color.red = 765 - c;
    color.green = 255;
    color.blue = 0;
  }
  if (c > 765 && c <= 1020){
    color.red = 0;
    color.green = 255;
    color.blue = c - 765;
  }
  if (c > 1020 && c <= 1275){
    color.red = 0;
    color.green = 1275 - c;
    color.blue = 255;
  }
  if (c > 1275 && c <= 1530){
    color.red = c - 1275;
    color.green = 0;
    color.blue = 255;
  }
  if (c > 1530 && c <= 1785){
    color.red = 255;
    color.green = 0;
    color.blue = 1785 - c;
  }
  return color;
}

int convergence(float x, float y)
{
  float complex u = x + y * I;
  float complex z = x + y *I;
  int counter = 0;
  while (counter < 86){
    if(cabsf(u) < 2){
      u = cpow(u,2) + z;
      counter++;
    }
    else{
      return counter;
    }
  }
  return 0;
}


int main(int argc, char**argv)
{
  FILE*fichier = NULL;
  fichier = fopen("image.ppm", "w+");
  if (fichier != NULL){
      fputs("P6", fichier);
      fputs("\n", fichier);
      fputs("900", fichier);
      fputs(" ", fichier);
      fputs("600", fichier);
      fputs("\n", fichier);
      fputs("255", fichier);
      fputs("\n", fichier);
      struct color v;
      for (float line = 300. ; line > -300.; line --){
        float g = line;
        g/=300.;
        for (float column = -600.; column < 300.; column ++){
          float h = column;
          h/=300.;
          int c = 100*convergence(h, g);
          v = palette(c);
          fprintf(fichier, "%c %c %c\n", v.red, v.green, v.blue);
        }
      }
      fclose(fichier);
  }
  else {
    printf("impossible d'ouvrir le fichier\n");
  }
  return 0;
}
