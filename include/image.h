#ifndef IMAGE_H
#define IMAGE_H

typedef struct
{
    unsigned char *pixels;
    int width;
    int height;
    int channels;
} Image;

Image load_img(const char *filename, int desired_channels);

void save_img(const char *filename, const Image *img);

// assumes dst length is img->width * img->height
void img_to_float(const Image *img, float *dst);

// assumes img->width and img->height are filled and width * height equals src length
void float_to_img(const float *src, Image *img);

void free_img(Image *img);

#endif
