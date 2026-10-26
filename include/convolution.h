#ifndef CONVOLUTION_H
#define CONVOLUTION_H

void convolve_scalar(const float *src, float *dst, 
    const float kernel[9], 
    int rows, int cols);

#endif