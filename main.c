#include "tp1.h"

struct color palette(int c)
{
  struct color color;
  color.red = 0;
  color.green = 0;
  color.blue = 0;

  for (;c > 1785; c -= 1785);

  switch (c) {
  // c >= 0 && c <= 255
  case 0 ... 255:
      color.red = c;
      break;
  case 256 ... 510:
      color.red = 255;
      color.green = c - 255;
      break;
  case 766 ... 1020:
      color.green = 255;
      color.blue = c - 765;
      break;
  case 1021 ... 1275:
      color.green = 1275 - c;
      color.blue = 255;
      break;
  case 1276 ... 1530:
      color.red = c - 1275;
      color.blue = 255;
      break;
  case 1531 ... 1785:
      color.red = 255;
      color.blue = 1785 - c;
      break;
  default:
      return color;
  }
  return color;
}

int convergence(float x, float y)
{
  float complex u = x + y * I;
  float complex z = x + y *I;
  int counter = 0;

  while (counter < 86){
    if (cabsf(u) < 2){
      u = cpow(u,2) + z;
      counter++;
    }
    else
      return counter;
  }
  return 0;
}


int main(int argc, char**argv)
{
  FILE*fichier = NULL;
  fichier = fopen("image.jpeg", "w+");

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
          int c = 100 * convergence(h, g);
          v = palette(c);
          fprintf(fichier, "%c %c %c\n", v.red, v.green, v.blue);
        }
      }
      fclose(fichier);
  }
  else
    printf("impossible d'ouvrir le fichier\n");
  return 0;
}
