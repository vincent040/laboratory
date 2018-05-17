#ifndef __MYHEAD_H_
#define __MYHEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MIN_PER_HOUR 60
#define SIZE 7

void perror_exit(const char *);
bool is_digit(const char *);
bool more_then(const char *, int);
bool s_fgets(char *, int, FILE *);

#endif
