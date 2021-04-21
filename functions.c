/** \file
 *
 * Hangman Program
 * @author Stefan Bittgen\n
 * Description: The program generates a random word from a provided *.txt file,
 * which works according to the well-known game "Hangman".
 * @date 22.01.2020
 */

#include "header.h"


#include <ctype.h>


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
void func(FILE **pToFile, int WordsReadIn, char **ptr, char input[], size_t arr_size, char *buffer) {

    int counter1, N;
    char *ptrToWord;
    char choice[1];
    char interWord;

//Open File stream for the stats with a+ (read and write access, file is appended, not replaced)
    FILE *text;
    text = fopen("stats.txt", "a+");

    if(text == NULL) {
        printf("Failed To Open 'text' File\n");
    }


    do{


        do{

//Makes use of the computer's internal clock to control the choice of the seed.
            srand(time(NULL));
            int randomIndex = rand() % WordsReadIn;

//Set stream back to the begin of file
            rewind(*pToFile);
//Only for testing purposes in the documentation. This command can be used to check at which point in the file we are currently located.
//printf("ftell --------->%ld\n", ftell(pToFile));

//Select random word which is 0 at begin
            for(counter1 = 0; counter1 < randomIndex; counter1++){
//Get the random selected word of the file
//Line by line, the word is fetched from pToFile and stored in input
                fgets(input, arr_size, *pToFile);
            }

        }while((input[0])!= '0');

        printf("The random word is %s\n", (*(ptr)));
        fprintf(text, "The random word is %s\n", (*(ptr)));
//We use strtok to remove the characters "0,\n\r" from the buffer in the file stream word.txt, so that we do not get the wrong position when going through the characters.
        ptrToWord=strtok(input, "0,\n\r");
        strcpy(buffer, ptrToWord);
//The function strcpy copies our ptrToWord to the buffer.

        if(text==NULL) {
            printf("Datei konnte nicht geöffnet werden.\n");
        } else {


// Set the mask array - mask[i] is true if the
// character s[i] has been guessed.  The mask
// must be allocated, and initialized to all false (0).
            N = strlen(*(ptr));
            int mask[N];
            for (int i=0; i < N; ++i) {
                mask[i] = 0;
            }



// Loop over each round of guessing
            int gameover = 0;

//The loop runs as long the attempts are not reached and the match is not yet won (1).
//The attempts are as many as the file is long + 5.
            for (int v = N + 5; v > 0 && gameover == 0; v--) 				{

// Print word with '_' for unguessed letters
                printf("The word is : ");
                fprintf(text, "The word is : ");

//++j increments variable directly, i++ increments variable after call
                for(int w=0; w < N; ++w) {

//If mask is true, print "1" for guessed character
                    if (mask[w]) {
                        printf("%c", (*(ptr))[w]);
                        fprintf(text,"%c", (*(ptr))[w]);
//If mask is not true, print "0"
                    }else {
                        printf("_ ");
                        fprintf(text,"_ ");

                    }
                }

                printf("\n");
                fprintf(text,"\n");


// Get player's next guess


                char guess[20];

                printf("You have %i tries left.\n", v);
                fprintf(text, "You have %i tries left.\n", v);

                printf("Letter? ");
                fprintf(text, "Letter? \n");
                fflush(stdout);
                scanf("%s", guess);
                fprintf(text, "%s\n", guess);



//If more than one letter is entered, it must be checked whether the word is correct or incorrect.
//If the entered word is correct gameover == 1 & the user has won, if the word is not correct gameover == 0 and User has lost!
                int P = (strlen(guess));
                if (P > 1) {
                    if (strcmp(*(ptr), guess) == 0) {
                        gameover = 1;
                        break;
                    } else if (strcmp(*(ptr), guess) != 0) {
                        gameover = 0;
                        break;
                    }
                }

//Checking whether the character is contained in the alphabet, if not, it gives a prompt to change it.
//isalpha checks if the passed character is alphabetic.
                for (int i = 0, alphabet = 0; guess[i] != '\0'; i++){
                    if (isalpha(guess[i]) != 0)
                        alphabet++;
                    else {
                        printf("Geben Sie einen Buchstaben ein: \n"
                               "Bitte verwenden Sie dazu nur das Alphabet (keine Sonderzeichen): ");
                        fprintf(text, "Geben Sie einen Buchstaben ein: \n"
                                      "Bitte verwenden Sie dazu nur das Alphabet (keine Sonderzeichen): ");
                        fflush(stdout);
                        scanf("%s", guess);
                        fputs(guess,text);
                    }
                }

//Mark true (1) all mask positions corresponding to guess

                for(int k=0; k < N; ++k) {
                    if (((*ptr)[k]) == *guess)
                        mask[k] = 1;
                }

//Determine whether the player has won!
                gameover = 1;
                for(int m = 0; m < N; ++m) {
//Go through mask 0,1,2,3,4,5,... and if any character in mask is 0, the game has not yet been won.
                    if (!mask[m]) {
                        gameover = 0;
                        break;
                    }
                }


            }

            if(gameover == 0){
                printf("Defeat! The word is \"%s\".\n", (*ptr));
                fprintf(text, "Defeat! The word is \"%s\".\n", (*ptr));
            } else {
                // Print victory message!
                printf("Victory! The word is \"%s\".\n", (*ptr));
                fprintf(text, "Victory! The word is \"%s\".\n", (*ptr));

            }


        }

        printf("Wanna play a new round? (Y/N)\n");
        fprintf(text,"Wanna play a new round? (Y/N) \n");

        scanf("%s", choice);
        fprintf(text, "%s\n", choice);

        if((choice[0] == 'n') || (choice[0] == 'N')){
            fprintf(text,"\n\n");
            break;

        }

        fprintf(text,"\n");

//We want to know the string length of the word (interWord).
//With "fseek" we start from the current position in our buffer (end of the word).
//We thus go back to the beginning of the word and replace the "0" with a "1"
//to mark the word as already used.
        interWord = strlen(input);
        fseek(*pToFile,-(interWord+1),SEEK_CUR);
//        printf("ftell --------->%ld\n", ftell(pToFile));
        fputs("1",*pToFile);


    }while(1);

//In the case our program ends prematurely (playing only one round), the word will still be marked in the file.
    interWord = strlen(input);
    fseek(*pToFile,-(interWord+1),SEEK_CUR);
    fputs("1",*pToFile);



// Flush stream and check whether successful

    if (fflush(text) != 0) {
        fprintf(stderr,"fflush was not successful!\n");
    }

// Flush stream and check whether successful
    if (fflush(*pToFile) != 0) {
        fprintf(stderr,"fflush was not successful!\n");
    }

}

