#include <stdlib.h>
#include <stdio.h>
#include "readfile.h"

FILE *file;

int open_file(char *openFile)
{
    file = fopen(openFile, "r");
    if (file == NULL)
    {
        printf("error");
        return -1;
    }
    return 0;
}

int close_file()
{
    if (file == NULL)
    {
        return -1;
    }
    fclose(file);
    return 0;
}

int read_line(char *buffer, int size)
{
    if (file == NULL)
    {
        return -1;
    }
    if (fgets(buffer, size, file) == NULL)
    {
        return -1;
    }
    return 0;
}

int read_int(int *var)
{
    return fscanf(file, "%d", var) == 1 ? 0 : -1;
}

int read_string(char *str)
{
    return fscanf(file, "%s", str) == 1 ? 0 : -1;
}

int read_float(float *var)
{
    return fscanf(file, "%f", var) == 1 ? 0 : -1;
}



