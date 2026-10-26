#include "convolution.h"
#include "image.h"
#include "kernel.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float kernel[9];
    load_kernel("data/kernel.txt", kernel);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("%.2f ", kernel[idx(i, j, 3)]);
        printf("\n");
    }

    const char *path = (argc > 1) ? argv[1] : "data/cat.png";

    Image img = load_img(path, 1);

    printf("pixel(0,0) = %3u\n", img.pixels[0]);
    printf("bytes = %zu\n",
           (size_t)img.width * (size_t)img.height * (size_t)img.channels);

    size_t pixel_count = (size_t)img.width * (size_t)img.height;
    float *src = xmalloc(sizeof(float), pixel_count);
    float *dst = xmalloc(sizeof(float), pixel_count);
    Image convolved_img = {.pixels = xmalloc(sizeof(unsigned char), pixel_count),
                           .height = img.height, .width=img.width, .channels = 1};

    img_to_float(&img, src);
    convolve_scalar(src, dst, kernel, img.height, img.width);
    float_to_img(dst, &convolved_img);
    save_img("data/cat_convolved.png", &convolved_img);
    
    free_img(&img);
    free_img(&convolved_img);
    free(src);
    free(dst);
    return 0;
}
