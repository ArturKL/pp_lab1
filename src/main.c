#include "image.h"
#include "util.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    const char *path = (argc > 1) ? argv[1] : "data/cat.png";

    Image img = load_img(path, 1);

    printf("pixel(0,0) = %3u\n", img.pixels[0]);
    printf("bytes = %zu\n",
           (size_t)img.width * (size_t)img.height * (size_t)img.channels);

	save_grayscale_img("data/cat_greyscale.png", &img);
    free_img(&img);
    return 0;
}
