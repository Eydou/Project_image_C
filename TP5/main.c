#include "bitmaplib.h"
#include "vectlib.h"


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
  base("cat.txt", noir, m);
  save_pic(m, "chat.ppm") ;
  return 0;
}
