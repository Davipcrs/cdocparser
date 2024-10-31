#include "cli.h"
#include "libcdocparser.h"
#include "menu.h"

void cli(int argc, char *argv[], parserType **programData){
    int ch = 0;
    
    //@DOCSTART
    // This is the code for garantee the output (-o) file
    //@CBS c
    
    char *output_path_auxiliar = NULL;

    while((ch = getopt_long(argc, argv, "ihf:d:o:c:", long_options, NULL)) != -1)){
        if(ch == 'c'){
            output_path_auxiliar = optarg;
            break;
        }
        else if(ch == 'i'){
            menu();
            return;
        }
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
                printf("file name: %s\n", optarg);
                break;
            }
            case 'd':{
                printf("dirname %s\n", optarg);
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