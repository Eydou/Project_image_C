#include "tp1.h"

int convergence(float x, float y)
{
    float complex u = x + y * I;
    float complex z = x + y *I;
    int counter = 0;

    while (counter < 86){
        if (cabsf(u) < 2) {
        u = cpow(u,2) + z;
        counter++;
        } else
        return counter;
    }
    return 0;
}

struct color palette(int c)
{
    struct color color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    for (;c > 1785; c -= 1785);

    switch (c) {
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

struct mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale)
{   
    struct mandel_pic mandel;
    mandel.convrg = malloc(sizeof(int)*(width * height));
    mandel.width = width;
    mandel.height = height;
    mandel.Xmin = Xmin;
    mandel.Ymin = Ymin;
    mandel.scale = scale;
    mandel.Xmax = Xmin + (scale * 3.0);
    mandel.Ymax = Ymin - (scale * 3.0 * height / width);
    mandel.pixwidth = scale * 3.0/width;

    return mandel;
}

void save_mandel(struct mandel_pic new_mandel, char* file)
{
    FILE *fichier = fopen(file, "w+");
    size_t inc = 0;
    size_t j = 0;
    size_t k = 0;

    if (fichier == NULL) {
        printf("Fichier non cree\n");
        return;
    }
    fprintf(fichier, "P6\n%d %d\n255\n",new_mandel.width, new_mandel.height);
    int nbre_pixel = (new_mandel.width) * (new_mandel.height);
    struct color a;

    for (double line = new_mandel.Ymin; line > new_mandel.Ymax; line -= 2. * (double)new_mandel.scale / (double)new_mandel.height) {
        j = 0;
        if (k == new_mandel.height)
        break;
        k++;
        for (double column = new_mandel.Xmin; column < new_mandel.Xmax; column += 3 * (double)new_mandel.scale / (double)new_mandel.width){
        new_mandel.convrg[inc] = 5 * convergence(column, line);
        if (j == new_mandel.width)
            break;
        j++;
        inc++;
        }
    }
    for (int i = 0; i < nbre_pixel; i++) {
        a = palette(new_mandel.convrg[i]);
        char color[3] = {a.red, a.green, a.blue};
        fwrite(color, 1, 3, fichier);
    }
    fclose(fichier);
}

int main(int argc, char**argv)
{
    FILE *fichier = NULL;
    struct mandel_pic m;

    m = new_mandel(900, 600, -0.755232, 0.121387, 0.01);
    save_mandel(m, "image2.ppm");
    if (!(fichier = fopen("image.jpeg", "w+"))) {
        printf("impossible d'ouvrir le fichier\n");
        return 0;
    }
    fprintf(fichier, "P6\n900 600\n255\n");
    struct color v;
    for (float line = 300. ; line > -300.; line --) {
        float g = line;
        g /= 300.;
        for (float column = -600.; column < 300.; column ++){
        float h = column;
        h /= 300.;
        int c = 5 * convergence(h, g);
        v = palette(c);
        char color[3] = {v.red, v.green, v.blue};
        fwrite(color, 1, 3, fichier);
        }
    }
    fclose(fichier);
    free(m.convrg);
    return 0;
}
