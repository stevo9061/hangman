#include "header.h"
#define MAXNUMWORDS 150
#define MAXWORDLENGTH 64
#define MAX_BUF 100

/**
 * This is the main program. It's open the File Stream for "stats.txt" and "words.txt"
 * @param argc This is a count of the arguments passed into main. We use it.
 * @param argv This is the array of arguments passed in to main. We use them.
 * @return The return will be 0.
 */
int main(int argc, char *argv[]) {


    char guessWords[MAXNUMWORDS][MAXWORDLENGTH];
    int WordsReadIn = 0;
    char buffer[MAX_BUF] = { "\0" };
    FILE *pToFile = NULL;

    readFile(&pToFile,argc,&argv[0],&buffer[0]);


    //Open File stream for the stats with a+ (read and write access, file is appended, not replaced)
    FILE *text;
    text = fopen("stats.txt", "a+");

    //Verifying that the paramter is not NULL, if so it puts an error message.
    if (text == NULL) {
        printf("Failed To Open File\n");
        return 0;
    }

    //Add current time to our game
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    //printf ("Current local time and date: %s", asctime(timeinfo));
    fprintf (text,"Current local time and date: %s", asctime(timeinfo));

    char input[63];
    char *ptr = input;

    //Line by line, the word is fetched from pToFile and stored in input
    while (fgets(input, 63, pToFile)) {
        //.. and input is read into guessWords[WordsReadIn], thus into our array.
        sscanf(input, "%s", guessWords[WordsReadIn]);
        //printf("Scanned: input:%s guessWords[%d]:%s\n",input,WordsReadIn,guessWords[WordsReadIn]);
        WordsReadIn++;
    }

    printf("Total Words Read In:%d\n", WordsReadIn);
    //This command also writes the output to our stats.txt
    fprintf(text, "Total Words Read In:%d\n", WordsReadIn);

    char choice[1];
    printf("Do you want to reset the Word File (Y/N)?\n");
    scanf("%s", choice);
    fprintf(text, "%s\n", choice);

    if((choice[0] == 'y') || (choice[0] == 'Y')) {
        rebuild();
    }


    // Flush stream and check whether successful

    if (fflush(text) != 0) {
        fprintf(stderr, "fflush was not successful!\n");
    }

    // We exit the the file stream.
    fclose(text);
    //fclose(pToFile);

    // The pointer starts at the start point from input + 2.
    ptr += 2;

    // Function call
    // In C, array parameters are treated as pointers. Therefore, sizeof should not be used to get number of elements in such cases.
    // A separate parameter for array size (or length) should be passed to fun().
    func(&pToFile, WordsReadIn, &ptr, input, 63, &buffer[0]);

    // We exit the the file stream.
    fclose(pToFile);

    return 0;

}


