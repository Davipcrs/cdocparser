#include "parser_data.h"

void addOutput(parserType ** programData, char *stringData){
    (*programData)->output_file = stringData;
    return;
}

void addFile(parserType ** programData, char *stringData){
    (*programData)->number_of_files = (*programData)->number_of_files + 1;
    char **temp = realloc((*programData)->input_files, (*programData)->number_of_files * sizeof(char *));
    if (temp == NULL)
    {
        perror("Failed to realloc memory");
        return; // Return NULL on failure
    }
    (*programData)->input_files = temp;
    (*programData)->input_files[(*programData)->number_of_files] = stringData;
    return;
}

void removeFileByIndex(parserType ** programData, int index){
    return;
}



int freeParserData(parserType ** programData){
    free((*programData)->output_file);
    int i = 0;
    while((*programData)->input_files[i] != NULL){
        free((*programData)->input_files[i]);
        i = i + 1;
    }
    //free((*programData)->input_files);
    //free((*programData));
    return 0;
}
