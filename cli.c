#include "cli.h"
#include "libcdocparser.h"
//#include "menu.h"
#include "src/utils/parser_data.h"
#include "src/utils/dir_utils.h"

void cli(int argc, char *argv[], parserType **programData){
    int ch = 0;
    
    //@DOCSTART
    // This is the code for garantee the output (-o) file
    //@CBS c
    
    char *output_path_auxiliar = NULL;

    while((ch = getopt_long(argc, argv, "ihf:d:o:c:", long_options, NULL)) != -1){
        if(ch == 'o'){
            output_path_auxiliar = optarg;
            addOutput(&programData, output_path_auxiliar);
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
                break;
            }
            case 'o':{
                // Already treated
                break;
            }
            case 'f':{
                addFile(&programData, optarg);
                break;
            }
            case 'd':{
                char ** helper = getAllFilesInTheDir(optarg);
                int i = 0;

	            while (helper[i] != NULL){
                    addFile(&programData, helper[i]);
                    free(helper[i]);
                    i = i + 1;
                }
                free(helper);
                break;
            }
            case 'c':{
                printf("raw code");
                break;
            }
            case 'h':{
                printf("help");
                break;
            }
            
            default:{
                printf("help");
            }
        }
    }
    return;
}