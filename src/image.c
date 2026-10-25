#include "image.h"
#include "util.h"

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#include <stdio.h>
#include <stdlib.h>

Image load_img(const char *filename, int desired_channels)
{
    Image img = {0};

    int channels_in_file = 0;

    img.pixels = stbi_load(filename, 
                           &img.width, 
                           &img.height, 
                           &channels_in_file,
                           desired_channels);

    if (img.pixels == NULL)
    {
        die("cannot load image '%s': %s", filename,
                stbi_failure_reason());
    }

    img.channels = (desired_channels != 0) ? desired_channels : channels_in_file;

    printf("%s: %dx%d px, %d channels (file has %d)\n", filename, img.width,
           img.height, img.channels, channels_in_file);

    return img;
}

void save_grayscale_img(const char *filename, const Image *img)
{
    int res = stbi_write_png(filename, 
                             img->width, 
                             img->height, 
                             1,
                             img->pixels,
                             img->width);

    if (res == 0)
    {
        die("cannot write image '%s'", filename);
    }
}

void free_img(Image *img)
{
    if (img == NULL)
        return;

    stbi_image_free(img->pixels);
    img->pixels = NULL;
    img->width = 0;
    img->height = 0;
    img->channels = 0;
}
