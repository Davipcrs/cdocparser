#ifndef PARSER_DATA_H
#define PARSER_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char **input_files
    int number_of_files
    char *output_file
} parserType;


void addOutput(parserType ** programData, char *stringData);
void addFile(parserType ** programData, char *stringData);
void removeFileByIndex(parserType ** programData, int index);
void changeOutput(parserType ** programData, char * stringData);
int freeParserData(parserType ** programData);

#endif