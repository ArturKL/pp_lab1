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

void save_grayscale_img(const char *filename, const Image *img);

void free_img(Image *img);

#endif
