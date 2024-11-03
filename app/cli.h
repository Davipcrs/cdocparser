#ifndef CLI_H
#define CLI_H
#include <getopt.h>
#include <stdlib.h>
#include "src/utils/consts_def.h"
#include <stdio.h>

static struct option long_options[] = 
{

{"menu", no_argument, NULL, 'i'},
{"help", no_argument, NULL, 'h'},
{"file", required_argument, NULL, 'f'},
{"directory", required_argument, NULL, 'd'},
{"output", required_argument, NULL, 'o'},
{"code", required_argument, NULL, 'c'},
{0,0,0,0}

};


void printHelp();
void cli(int argc, char *argv[], parserType **programData);


#endif