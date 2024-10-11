#include <stdio.h>
#include "consts_def.h"
#include "file_preprocessor.h"

int main()
{
	char *data = loadFile("./file_preprocessor.c");
	char *r = removeNonComments(data);
	printf("%s", r);
	return 0;
}