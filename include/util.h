#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

[[noreturn]] void die(const char *message);

void *xmalloc(size_t size, size_t elem_count);
void *xcalloc(size_t size, size_t elem_count);

#define new(T) ((T *)xcalloc(1, sizeof(T)))

void init_rand(float *grid, size_t width, size_t height);

static inline size_t idx(size_t i, size_t j, size_t width)
{
    return i * width + j;
}

#endif
