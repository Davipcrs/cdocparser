#include <stdio.h>
#include "src/consts_def.h"
#include "src/file_preprocessor.h"
#include "src/comments_reader.h"

int main()
{
	char *data = loadFile("./src/file_preprocessor.c");
	// printf("%s", data);

	char *r = removeNonComments(data);
	// printf("%s", r);
	const char *reader = docExtractor(r);
	printf("%s", reader);
	//    printf("%s", r);
	free(data);
	free(r);
	// free(reader);
	return 0;
}