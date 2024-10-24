// @ID ## main.c @NL

// @DOCSTART

// #### Using the project @NL
// To use the project you need to use anotations "@SOMETHING" inside comments (WITH THE "@")to generate docs. Substitute the "SOMETHING" with this anotations: @NL
// @NL - DOCSTART (For starting a doc block) @NL
// @NL - DOCENT (For ending a doc block) @NL
// @NL - ID or INLINEDOC (For inline doc - No need to create a doc block) @NL
// @NL - NL (For new Line) @NL
// @NL - CODEBLOCKSTART or CBS (For creating a Code Block [Include no Commentary in the doc]) @NL
// @NL - CODEBLOCKEND or CBE (For Ending a code block) @NL
// More on Code Blocks later in the doc @NL
// ###### Code Blocks @NL
// Here you can include code blocks in the documentation
// Its Better to use CBS and CBE and with this structure: @NL
// @NL - DOCSTART @NL
// @NL - CBS [Language, in this case c] @NL
// @NL - "CODE" @NL
// @NL - CBE @NL
// @NL - NL @NL
// @NL - DOCEND @NL
// @DOCEND

#include <stdio.h>
#include "src/utils/consts_def.h"
#include "src/file_preprocessor.h"
#include "src/comments_reader.h"
#include "src/utils/str_utils.h"
#include "src/utils/dir_utils.h"
#include "src/exporter.h"

int main()
{
	const char *dir = getCurrentDir();

	// printf("%s\n", dir);
	// getAllFilesInTheDir(dir, 10);
	const char **files = getAllFilesInTheDir(dir);
	// printf("%lu", sizeof(files));
	// printStrings(files);
	int i = 0;

	while (files[i] != NULL)
	{
		char *data = loadFile(files[i]);
		// printf("%s", data);

		char *r = removeNonComments(data);
		// printf("%s", r);

		const char *reader = docExtractor(r);
		// printf("%s", reader);
		//         printf("%s", r);

		const char *result = removeSpaces(reader);
		// printf("%s", result);

		const char *exported = formatString(result, 1);
		// printf("%s", exported);

		const char *last = formatCB(exported, 2);
		// printf("EXPORTED2: %s\n\n", last);

		mdExporter("docs.md", last);

		// free(data);
		// free(r);
		// free(reader);
		free(r);
		free(reader);
		free(result);
		free(exported);
		i = i + 1;
	}
	/*
	char *data = loadFile("src/file_preprocessor.c");
	// printf("RAW: %s\n\n", data);

	char *r = removeNonComments(data);
	// printf("NO COMMENTS: %s\n\n", r);
	const char *reader = docExtractor(r);
	// printf("EXTRACTOR: %s\n\n", reader);
	//          printf("%s", r);

	const char *result = removeSpaces(reader);
	// printf("SPACES: %s\n\n", result);

	const char *exported = formatString(result, 2);
	// printf("EXPORTED: %s\n\n", exported);

	const char *last = formatCB(exported, 2);
	// printf("EXPORTED2: %s\n\n", last);

	mdExporter("docs.md", last);
	*/
	return 0;
}