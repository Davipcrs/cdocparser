#include <stdio.h>
#include "consts_def.h"
#include "file_preprocessor.h"
#include "comments_reader.h"

int main()
{
	char *data = loadFile("./file_preprocessor.c");
	char *r = removeNonComments(data);
	const char *reader = docExtractor(r);
	printf("%s", reader);
	// printf("%s", r);
	free(data);
	free(r);
	// free(reader);
	return 0;
}