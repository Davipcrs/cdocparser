#ifndef PARSER_DATA_H
#define PARSER_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char **input_files;
    int number_of_files;
    int clicode;
    char *output_file;
} parserType;


void addOutput(parserType ** programData, char *stringData);
void addFile(parserType ** programData, char *stringData);
void removeFileByIndex(parserType ** programData, int index);
int freeParserData(parserType ** programData);

#endif