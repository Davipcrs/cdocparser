// @ID ## parser_data.c @NL

#include "parser_data.h"
#include <string.h>

void addOutput(parserType ** programData, char *stringData){
    (*programData)->output_file = stringData;
    return;
}

void addFile(parserType ** programData, char *stringData){
    // @DOCSTART
    // @CBS c
    // This + 1 in the following code is for the allocation to work when number_of_files = 0;
    char **temp = realloc((*programData)->input_files, ((*programData)->number_of_files + 1) * sizeof(char *));
    //@CBE
    //@NL
    //@DOCEND

    if (temp == NULL)
    {
        perror("Failed to realloc memory");
        return; // Return NULL on failure
    }
    (*programData)->input_files = temp;
    (*programData)->input_files[(*programData)->number_of_files] = stringData;
    //printf("%s\n",(*programData)->input_files[(*programData)->number_of_files]);
    (*programData)->number_of_files = (*programData)->number_of_files + 1;
    return;
}

void removeFileByIndex(parserType ** programData, int index){
    return;
}



int freeParserData(parserType ** programData){
    //free((*programData)->output_file);
    int i = 0;
    for(i = 0; i < (*programData)->number_of_files; i = i + 1);
    {
        free((*programData)->input_files[i]);
    }
    free((*programData)->input_files);
    free(*programData);
    *programData = NULL;

    return 0;
}
