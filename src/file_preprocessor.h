#ifndef FILE_PREPROCESSOR_H
#define FILE_PREPROCESSOR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "utils/consts_def.h"

char *loadFile(const char *path);
char *removeNonComments(char *input);
#endif

// https://chatgpt.com/c/67086127-c9d0-800b-9c4b-586f9c2a0022