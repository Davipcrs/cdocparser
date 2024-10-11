#include <string.h>;
#include <stdio.h>;
#include <stdlib.h>;
#include "consts_def.h";

struct cdstring
{
    char data[4096];
    int lenght;
};

int checkTokens();
void checkComments();
int checkTokenBlock();
