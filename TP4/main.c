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

void base(char * file, struct color c, struct picture m)
{
  FILE *fich = fopen(file, "r");
  float x1, y1, x2, y2;
  while(fscanf(fich, "%f %f %f %f", &x1, &y1, &x2, &y2) != EOF)
  {
    draw_line(m, x1, y1, x2, y2, c);
  }
  fclose(fich);
}

struct vector read_vector_file(char *file)
{
  struct vector v;
  FILE * fichier = fopen(file, "r");
  struct vector* first = NULL;
  struct vector* new = malloc(sizeof(struct vector));
  fscanf(fichier, "%lf %lf %lf %lf", &v.x1, &v.y1, &v.x2, &v.y2);

}

int main(int argc, char**argv)
{
  struct picture m = new_pic(500,500);
  struct color rouge = {255, 0, 0};
  struct color bleu = {0, 0, 255};
  struct color magenta = {255, 0, 255};
  struct color vert = {0, 255, 0};
  struct color blanc = {255, 255, 255};
  struct color noir = {0, 0, 0};
  for (int i = 0; i < m.width; i++){
    for (int j = 0; j < m.height; j++){
        set_pixel(m, i, j, blanc);
    }
  }

  save_pic(m, "image1.ppm") ;
  return 0;
}
