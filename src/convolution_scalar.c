#include "convolution.h"
#include "util.h"
#include <stddef.h>

float apply_kernel_scalar(const float *src, 
    const float kernel[9], int width, int i, int j)
{
    float value = 0;
    for (int k = -1; k < 2; k++)
    {
        value += kernel[idx(k + 1, 0, 3)] * src[idx(i + k, j - 1, width)];
        value += kernel[idx(k + 1, 1, 3)] * src[idx(i + k, j, width)];
        value += kernel[idx(k + 1, 2, 3)] * src[idx(i + k, j + 1, width)];
    }
    return value;
}

void convolve_scalar(const float *src, float *dst,
    const float kernel[9],
    int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            size_t index = idx(i, j, cols);
            // border stays unchanged
            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
            {
                dst[index] = src[index];
                continue;
            }

            dst[index] = apply_kernel_scalar(src, kernel, cols, i, j);
        }
    }
}