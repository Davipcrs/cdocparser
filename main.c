// @ID ## main.c @NL

// @DOCSTART

// #### Using the project @NL
// To use the project you need to use anotations "@SOMETHING" inside comments (WITH THE "@")to generate docs. Substitute the "SOMETHING" with this anotations: @NL
// @NL - DOCSTART (For starting a doc block) @NL
// @NL - DOCEND (For ending a doc block) @NL
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
//#include "app/menu.h"
#include "cli.h"
#include "src/file_preprocessor.h"
#include "src/comments_reader.h"
#include "src/utils/str_utils.h"
#include "src/utils/dir_utils.h"
#include "src/exporter.h"
#include "src/utils/parser_data.h"

int main(int argc, char *argv[])
{

	parserType *myData = malloc(sizeof(parserType));
	myData->number_of_files = 0;
	myData->output_file = "docs.md";
	myData->input_files = malloc(1 * sizeof(char *));
	/*
	if (argc == 1)
	{
		//char * currentDir = getCurrentDir();
		//char ** files = getAllFilesInTheDir(currentDir);
		//free(currentDir);
		//int i = 0;
		//while(files[i] != NULL){
		//	free(files[i]);
		//	i = i + 1;
		//}
		//free(files);
		menu(&myData);
	}
	else
	{
		
		cli(argc, argv, &myData);
		
	}
	*/
	if(argc == 1){
		printHelp();
		return 0;
	}
	cli(argc, argv, &myData);	
	if(myData->number_of_files == 0){
		const char *dir = getCurrentDir();
		const char **files = getAllFilesInTheDir(dir);
		myData->input_files = files;
	}
	if(myData->clicode == 0){
		return 0;
	}
	/*
	const char *dir = getCurrentDir();

	// printf("%s\n", dir);
	// getAllFilesInTheDir(dir, 10);
	const char **files = getAllFilesInTheDir(dir);
	// printf("%lu", sizeof(files));
	// printStrings(files);
	int i = 0;
	*/
	int i = 0;
	while (myData->input_files[i] != NULL)
	{
		printf("\n");
		printf("Loading file: ");
		printf("%s\n",myData->input_files[i]);

		char *data = loadFile(myData->input_files[i]);
		// printf("%s", data);
		
		char *r = removeNonComments(data);
		// printf("%s", r);
		
		char *reader = docExtractor(r);
		// printf("%s", reader);
		//         printf("%s", r);

		const char *result = removeSpaces(reader);
		// printf("%s", result);

		const char *exported = formatString(result, 1);
		// printf("%s", exported);

		char *last = formatCB(exported, 2);
		// printf("EXPORTED2: %s\n\n", last);

		printf("Exporting to %s...\n", myData->output_file);
		mdExporter(myData->output_file, last);

		//free(data);
		free(r);
		free(reader);
		free(result);
		free(exported);
		free(last);
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

	freeParserData(&myData);
	return 0;
}