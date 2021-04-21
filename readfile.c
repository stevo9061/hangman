/** \file
 *
 * Hangman Program
 * @author Stefan Bittgen\n
 * Description: With func. readfile.c, other *.text files can also be used by getopt via -fexample.txt.
 * @date 22.01.2020
 */

#include "header.h"

#include <unistd.h>
#include <getopt.h>


/**
 * This function allows the user to select a text file of his choice.
 * @param **pToFile: We get pToFile passed from main and use it to open a filestream.
 * @param argc This is a count of the arguments passed into main. We use it.
 * @param argv This is the array of arguments passed in to main. We use them.
 */

unsigned int readFile(FILE **pToFile,int argc, char **argv,char *buffer)
{
    int retValue;
    char opts[] = "f:";
    while ((retValue = getopt(argc, argv, opts)) != -1) {

        switch (retValue) {
            case 'f':
                strcpy(buffer, optarg);
                break;
            default:
                return 1;
        }
    }
    *pToFile = fopen(buffer, "r+");
    if (*pToFile == NULL) {
        printf("Failed To Open File\n");
    }

    return 0;
}
