#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void appendString(char **dest, const char *src, size_t *currentSize);
void removeSpaces();
void formatString();

#endif