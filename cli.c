// @ID ##cli.c
#include "cli.h"
#include "libcdocparser.h"
//#include "menu.h"
#include "src/utils/parser_data.h"
#include "src/utils/dir_utils.h"

void printHelp(){
    printf("Usage: cdocparser [options]\n\n");
    printf("Options:\n");
    //printf("  -i             Opens an interactive menu.\n");
    printf("  -h             Show this help message.\n");
    printf("  -f <file>      Pass a file to the program. Can be used multiple times.\n");
    printf("                 Example: -f /path/to/file1 -f /path/to/file2\n");
    printf("  -d <dir>       Pass a directory to the program.\n");
    printf("  -o <output>    Specify the output file. Must be used only once.\n");
    //printf("  -c <code>      Pass raw code to the output file. (Not yet implemented)\n\n");
    printf("Examples:\n");
    //printf("  cdocparser -i\n");
    printf("  cdocparser -f /path/to/file -o output.md\n");
    printf("  cdocparser -o output.md\n");
    printf("  cdocparser -f /path/to/file\n");
    printf("  cdocparser -d /path/to/dir\n");
    printf("  cdocparser -d /path/to/dir  -o output.md\n");
    //printf("  cdocparser -c \"print('Hello, World!')\" -o output.txt\n\n");
    //printf("Notes:\n");
    //printf("  - Options `-f` and `-d` can be used together to specify files and directories.\n");
    //printf("  - `-o` is mandatory if output is required.\n");
    //printf("  - `-c` option is currently not functional.\n");

    return;
}

void cli(int argc, char *argv[], parserType **programData){
    int ch = 0;
    
    //@DOCSTART
    // This is the code for garantee the output (-o) file
    //@CBS c
    
    char *output_path_auxiliar = NULL;
    char ** helper = malloc(1 * sizeof(char *));
    while((ch = getopt_long(argc, argv, "ihf:d:o:c:", long_options, NULL)) != -1){
        if(ch == 'o'){
            output_path_auxiliar = optarg;
            addOutput(programData, output_path_auxiliar);
            break;
        }
        /*
        else if(ch == 'i'){
            menu();
            return;
        }
        */
    }

    optind = 1;
    
    //@CBE
    //@NL
    //@DOCEND

    while((ch = getopt_long(argc, argv, "ihf:d:o:c:", long_options, NULL)) != -1){
        switch(ch){
            case 'i':{
                // Already treated 
                printHelp();
                (*programData)->clicode = 0;              
                break;
            }
            case 'o':{
                // Already treated
                (*programData)->clicode = 1;
                break;
            }
            case 'f':{
                addFile(programData, optarg);
                (*programData)->clicode = 1;
                break;
            }
            case 'd':{
                // @ID -d --directory needs to be corrected - Giving a SegFault
                //printHelp();
                (*programData)->clicode = 1;
                // use srtcpy
                
                helper = getAllFilesInTheDir(optarg);
                int i = 0;

	            while (helper[i] != NULL){
                    addFile(programData, helper[i]);
                    //free(helper[i]);
                    i = i + 1;
                }
                
                break;
            }
            case 'c':{
                printHelp();
                (*programData)->clicode = 0;
                break;
            }
            case 'h':{
                printHelp();
                (*programData)->clicode = 0;
                break;
            }
            
            default:{
                printHelp();
                (*programData)->clicode = 0;
                break;
            }
        }
    }
    free(helper);
    return;
}