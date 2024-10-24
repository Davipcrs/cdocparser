// @ID ## file_preprocessor.c @NL

#include "file_preprocessor.h"

char *loadFile(const char *path)
{

	/*
	@DOCSTART
	This function is the function responsible to implement the file loading.@NL
	In the input is a char point (A string) for the path of the file. @NL
	@DOCEND
	*/

	FILE *file;
	char buffer[FILE_CHUNK_SIZE];
	char *fileContent = NULL;
	size_t bytesRead;
	size_t totalSize = 0;

	file = fopen(path, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return "File is NULL, check the reference";
	}

	// read file content
	while ((bytesRead = fread(buffer, 1, FILE_CHUNK_SIZE, file)) > 0)
	{
		char *auxiliarChar = realloc(fileContent, totalSize + bytesRead);
		if (auxiliarChar == NULL)
		{
			if (fileContent == NULL)
			{
				perror("Error: File has NULL data");
				fclose(file);
				// free(fileContent);
				return "File has NULL data inside";
			}
			perror("Error: Can't realloc memory");
			fclose(file);
			return fileContent;
		}
		fileContent = auxiliarChar;

		memcpy(fileContent + totalSize, buffer, bytesRead);
		totalSize += bytesRead;
		// free(auxiliarChar);
	}

	// check errors
	if (ferror(file))
	{
		perror("Error reading file");
		free(fileContent);
		fclose(file);
		return "File read error";
	}

	fclose(file);

	// check errors
	fileContent = realloc(fileContent, totalSize + 1); // One extra byte for the null terminator
	if (fileContent == NULL)
	{
		perror("Memory allocation failed");
		return "mem error";
	}

	// add the null terminator
	fileContent[totalSize] = '\0';

	return fileContent;
}

char *removeNonComments(char *input)
{
	// @DOCSTART
	// @CBS c
	bool isSingleLine = false;
	bool isInMultiLine = false;
	bool isCodeBlock = false;
	int saveIndexOfStartComment_aux1 = 0;
	int saveIndexOfStartComment_aux2 = 0;
	int readIndex = 0;
	int inputLength = strlen(input);
	int returnStringWriteIndex = 0;
	// char returnString[inputLength + 1];
	char *returnString = realloc(input, (inputLength + 1) * sizeof(char));
	// @CBE
	// @NL
	// @DOCEND

	if (returnString == NULL)
	{
		perror("memory error");
		return "Insert comments in the file";
	}

	while (readIndex < inputLength)
	{
		// Check if is in no block and if is a blank space
		if (!isSingleLine && !isInMultiLine && isspace(input[readIndex]))
		{
			readIndex++;
			continue;
		}

		// Check if is a single line comment
		if (!isSingleLine && input[readIndex] == '/' && input[readIndex + 1] == '/')
		{
			isSingleLine = true;
			saveIndexOfStartComment_aux1 = readIndex;
			saveIndexOfStartComment_aux2 = readIndex + 1;
		}

		// Check if is a MULTI line comment
		if (!isInMultiLine && input[readIndex] == '/' && input[readIndex + 1] == '*')
		{
			isInMultiLine = true;
			saveIndexOfStartComment_aux1 = readIndex;
			saveIndexOfStartComment_aux2 = readIndex + 1;
		}

		if (!isCodeBlock && (strncmp(input + readIndex, CODEBLOCKSTART, 15) == 0 || strncmp(input + readIndex, CBS, 4) == 0))
		{
			isCodeBlock = true;
			continue;
		}

		// Treat the comments:
		if (isSingleLine)
		{
			// Check single line end
			if (input[readIndex] == '\n')
			{
				isSingleLine = false; // Fim do comentário de linha única
			}
			if (saveIndexOfStartComment_aux1 == readIndex)
			{
				readIndex++;
			}
			if (saveIndexOfStartComment_aux2 == readIndex)
			{
				readIndex++;
			}
			returnString[returnStringWriteIndex] = input[readIndex];
			returnStringWriteIndex++;
			readIndex++;
			continue;
		}

		// Enquanto estivermos dentro de um comentário multilinha, copiamos até encontrar '*/'
		if (isInMultiLine)
		{
			if (input[readIndex] == '*' && input[readIndex + 1] == '/')
			{
				isInMultiLine = false;
				continue; // Fim do comentário multilinha
			}
			if (saveIndexOfStartComment_aux1 == readIndex)
			{
				readIndex++;
			}
			if (saveIndexOfStartComment_aux2 == readIndex)
			{
				readIndex++;
			}
			returnString[returnStringWriteIndex] = input[readIndex];
			returnStringWriteIndex++;
			readIndex++;
			continue;
		}

		// printf("Valor do isCodeBlock: %d\n", isCodeBlock);
		while (isCodeBlock && !isInMultiLine && !isSingleLine)
		// needs to debug the CBE.
		{
			// printf("%s\n", input + readIndex);
			if (strncmp(input + readIndex - 13, CODEBLOCKEND, 13) == 0 || strncmp(input + readIndex - 4, CBE, 4) == 0)
			{

				isCodeBlock = false;
				break;
			}
			returnString[returnStringWriteIndex] = input[readIndex];
			returnStringWriteIndex++;
			readIndex++;
			continue;
		}

		readIndex++;
	}

	returnString[returnStringWriteIndex] = '\0';
	// returnString[readIndex] = '\0';
	return returnString;
}