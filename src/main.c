#include "image.h"
#include "kernel.h"
#include "util.h"

#include <stdio.h>

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

    save_grayscale_img("data/cat_greyscale.png", &img);
    free_img(&img);
    return 0;
}
