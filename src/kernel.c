#include "kernel.h"
#include "util.h"

#include <stdio.h>

void load_kernel(const char *filename, float kernel[9])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        die("cannot open kernel file '%s'", filename);
    }

    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2)
    {
        fclose(file);
        die("cannot read kernel dimensions from '%s'", filename);
    }

    if (rows != 3 || cols != 3)
    {
        fclose(file);
        die("expected a 3x3 kernel in '%s', got %dx%d",
            filename, rows, cols);
    }

    for (int i = 0; i < 9; i++)
    {
        if (fscanf(file, "%f", &kernel[i]) != 1)
        {
            fclose(file);
            die("invalid or missing coefficient %d in '%s'",
                i, filename);
        }
    }

    fclose(file);
}