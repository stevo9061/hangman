/** \file
 *
 * Hangman Program
 * @author Stefan Bittgen\n
 * Description: With func. rebuild.c the already used and marked words can be reset.
 * @date 22.01.2020
 */


#include "header.h"


/**
 * This sub function opens a filestream with words.txt and resets the words already used and replaces the '1' with '0'.
 */
void rebuild()
{

//Open File for the words with r+ (read & write access, existing file can be overwritten)
    FILE *rst = fopen("words.txt","r+");
    int c;

    if(rst == NULL) {
        printf("Failed To Open 'text' File\n");
    }
    fseek(rst, 0, SEEK_SET);
    while((c = fgetc(rst)) != EOF)
    {
//Set the '1' to a '0' back.
        if(c == '1')
        {
            c = fgetc(rst);
            fseek(rst, -2, SEEK_CUR);
            fputc('0', rst);
        }
    }

    fclose(rst);

}
