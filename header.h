/** \file
 * Hangman Program
 * @author Stefan Bittgen
 * Description: The program generates a random word from a provided *.txt file,
 * which works according to the well-known game "Hangman".
 * You can also use your own text file with filled words.
 * @date 22.01.2020
 */

#ifndef HANGMAN_HEADER_H
#define HANGMAN_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * This sub function allows the user to select a text file of his choice.
 * @param **pToFile: We get pToFile passed from main and use it to open a filestream.
 * @param argc This is a count of the arguments passed into main. We use it.
 * @param argv This is the array of arguments passed in to main. We use them.
 */

unsigned int readFile(FILE **pToFile,int argc, char **argv,char *buffer);



/**
 * This sub-function opens a file stream from our standard words.txt and resets the words already used and replaces the '1' with '0'.
 */
void rebuild();


/**
 * This main function opens a filestream for *text, pToFile should already be open as we have already selected the *.txt file
 * when running the program. Match histories are stored in stats.txt and random words are fetched default from words.txt.
 * Furthermore, various other functionalities are provided. The other code is explained at the individual points in program.
 * @param **pToFile: We transfer the already open filestream to the correspondingly selected text file.
 * @param WordsReadin: This integer shows how many words are fetched from the text file.
 * @param **ptr: This ptr is used to manipulate the starting point from the array. We don't want to start guessing from "0,erratemich", we want to start from the start postion +2.
 * That is the reason why we used the pointer, its easier to handling as with an array.
 * @param input[]: This is a pointer to the start point from the imported array. An example is "0" because our words starts with zero.
 * @param size_t arr_size: We cannot give over a function the size from our array, therefore we use size_t.
 * @param *buffer: The buffer gives me the size of the string with.
 */
void func(FILE **pToFile, int WordsReadIn, char **ptr, char input[], size_t arr_size, char *buffer);


#endif //HANGMAN_HEADER_H
