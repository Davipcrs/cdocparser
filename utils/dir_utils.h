#ifndef DIR_UTILS_H
#define DIR_UTILS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../src/consts_def.h"

char *getCurrentDir();
char **getAllFilesInTheDir(char *directory, int numberOfFiles);
#endif