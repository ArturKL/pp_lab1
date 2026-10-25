#include "util.h"

#include <stdarg.h>
#include <stdckdint.h>
#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t size, size_t elem_count)
{
    size_t total_size = 0;

    if (ckd_mul(&total_size, size, elem_count))
        die("memory allocation size overflow");

    void *memory = malloc(total_size);

    if (memory == nullptr)
        die("memory allocation error");

    return memory;
}

void *xcalloc(size_t size, size_t elem_count)
{
    void *memory = calloc(size, elem_count);

    if (memory == nullptr)
        die("memory allocation error");

    return memory;
}

void die(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
    exit(EXIT_FAILURE);
}

void init_rand(float *grid, size_t width, size_t height)
{
    for (size_t i = 1; i < height - 1; i++)
    {
        for (size_t j = 1; j < width - 1; j++)
        {
            size_t index = idx(i, j, width);

            grid[index] = (float)(rand() % 2);
        }
    }
}
