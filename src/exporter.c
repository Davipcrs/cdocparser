#include "exporter.h"

void mdExporter(const char *outputPath, const char* data){

    // create file for saving the 
    // docs

    FILE *file;


    file = fopen(outputPath, "a");

    if(data != NULL){
        fputs(data, file);
    }

    fclose(file);

    return;
}
void txtExporter(const char *outputPath, const char* data){
    mdExporter(outputPath, data);
}
