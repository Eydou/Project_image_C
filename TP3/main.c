#include "tp3.h"


struct picture new_pic(int width, int height)
{   
  struct picture pic;
  struct color color;
    struct color* tab = malloc(sizeof(int)*3*width*height);
    pic.pixels = tab;
    pic.width = width;
    pic.height = height;
    return pic;
}

void save_pic(struct picture new_pic, char* file)
{
  FILE * fichier = fopen(file, "w+");
  if (fichier == NULL)
    printf("Fichier non cree\n");
  else {
    fprintf(fichier, "P6\n%d %d\n255\n",new_pic.width, new_pic.height);
    for (int i = 0; i < new_pic.width*new_pic.height; i++){
      fwrite(new_pic.pixels+i, 1, 3, fichier);
    }
    fclose(fichier);
  }
}


void set_pixel(struct picture a, int x, int y, struct color couleur)
{
  *(a.pixels+x+y*a.width) = couleur;
}

void draw_line(struct picture pic, int x1, int y1, int x2, int y2, struct color couleur)
{
  int n = fmax(abs(x1 - x2),abs(y1 - y2))+1;
  for (int i = 0; i < n; i++){
    set_pixel(pic, (x1*i)/(n-1) + x2 - (x2*i)/(n-1), (y1*i)/(n-1) + y2 - (y2*i)/(n-1), couleur);
  }
}

void sierpinski(struct picture pic, double x, double y, double taille, struct color couleur)
{
  double b=-taille*sqrt(3.0)/2;
  if (taille > 2){
  draw_line(pic, x, y, x + taille/2 - 1, y + b, couleur);
  draw_line(pic, x, y, x + taille-1, y, couleur);
  draw_line(pic, x + taille - 1, y, x + taille/2 - 1, y + b, couleur);
  sierpinski(pic, x, y, taille/2, couleur);
  sierpinski(pic, x + taille/2, y, taille/2, couleur);
  sierpinski(pic, x + taille/4, y + b/2, taille/2, couleur);
  }
}

int main(int argc, char**argv)
{
    struct picture m = new_pic(400,350);
    struct color rouge = {255, 0, 0};
    struct color bleu = {0, 0, 255};
    struct color magenta = {255, 0, 255};
    struct color vert = {0, 255, 0};
    struct color blanc = {255, 255, 255};
    for (int i = 0; i < m.width; i++){
      for (int j = 0; j < m.height; j++){
          set_pixel(m, i, j, blanc);
     }
    }
  sierpinski(m, 0, 349, 400, rouge);
  save_pic(m, "image1.ppm") ;
  return 0;
}
