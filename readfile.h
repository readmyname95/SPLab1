#ifndef _READFILE_H_
#define _READFILE_H_
#include <stdio.h>

/*
extern int read_int(char x[], int option, int* var);
extern int read_string(char x[], int option, char y[]);
extern int read_float(char x[], int option, float* var);
*/

extern int read_int(int* var);
extern int read_string(char y[]);
extern int read_float(float* var);
extern int open_file(char* filename);
extern int close_file();
extern int read_line(char line[], int maxLen);

#endif
