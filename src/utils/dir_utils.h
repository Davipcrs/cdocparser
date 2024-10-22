// @ID ## dir_utils.h @NL
// @ID This is the Header file for the Dir Utils @NL

#ifndef DIR_UTILS_H
#define DIR_UTILS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "consts_def.h"

#ifdef _WIN32
#include <direct.h> // For Windows
#define getcwd _getcwd
#else
#include <unistd.h> // For Linux/macOS
#endif

#define PATH_MAX 4096

char *getCurrentDir();
char **getAllFilesInTheDir(char *directory);
void allocStr(char ***array, int size);
void printStrings(char **array);
#endif