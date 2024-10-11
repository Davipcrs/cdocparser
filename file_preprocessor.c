#include "file_preprocessor.h"

char *loadFile(const char *path)
{
	FILE *file;
	char buffer[FILE_CHUNK_SIZE];
	char *fileContent = NULL;
	size_t bytesRead;
	size_t totalSize = 0;

	file = fopen(path, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return 'File is NULL, check the reference';
	}

	while ((bytesRead = fread(buffer, 1, FILE_CHUNK_SIZE, file)) > 0)
	{
		char *auxiliarChar = realloc(fileContent, totalSize + bytesRead);
		if (auxiliarChar == NULL)
		{
			if (fileContent == NULL)
			{
				perror("Error: File has NULL data");
				fclose(file);
				free(fileContent);
				return "File has NULL data inside";
			}
			perror("Error: Can't realloc memory");
			fclose(file);
			return fileContent;
		}
		fileContent = auxiliarChar;

		memcpy(fileContent + totalSize, buffer, bytesRead);
		totalSize += bytesRead;
		free(auxiliarChar);
	}

	if (ferror(file))
	{
		perror("Error reading file");
		free(fileContent);
		fclose(file);
		return 'File read error';
	}

	fclose(file);

	fileContent = realloc(fileContent, totalSize + 1); // One extra byte for the null terminator
	if (fileContent == NULL)
	{
		perror("Memory allocation failed");
		return 'mem error';
	}

	fileContent[totalSize] = '\0';

	return fileContent;
}

void removeNonComments(char *input, char *output)
{
	printf("%s\n", DOCSTART);
	return;
}