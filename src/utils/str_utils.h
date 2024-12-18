// @ID ## str_utils.h @NL
// @ID This is the Header file for the Str Utils. @NL
#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "consts_def.h"

// @DOCSTART @NL
// Functions defined:
// @CBS c
void appendString(char **dest, const char *src, size_t *currentSize);
const char *removeSpaces(const char *str);
const char *checkFirstOccurrence(const char *str);
const char *formatString(const char *str, int exportType);
char *formatCB(const char *str, int exportType);
// @CBE
// @NL
// @DOCEND
#endif