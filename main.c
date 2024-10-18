#include <stdio.h>
#include "src/consts_def.h"
#include "src/file_preprocessor.h"
#include "src/comments_reader.h"
#include "utils/str_utils.h"
#include "utils/dir_utils.h"

int main()
{
	const char *dir = getCurrentDir();
	/*
	char *data = loadFile("./src/file_preprocessor.c");
	// printf("%s", data);

	char *r = removeNonComments(data);
	// printf("%s", r);
	const char *reader = docExtractor(r);
	// printf("%s", reader);
	//     printf("%s", r);

	const char *result = removeSpaces(reader);
	// printf("%s", result);

	const char *exported = formatString(result, 2);
	//printf("%s", exported);

	*/
	printf("%s", dir);

	// free(data);
	// free(r);
	//  free(reader);
	return 0;
}