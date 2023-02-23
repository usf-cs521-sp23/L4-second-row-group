#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define COLOR_NONE "\033[0m"
#define RED "\033[1;31;40m" 
#define GREEN "\033[1;32;40m"
#define YELLOW "\033[1;33;40m"
#define MAX_WORDS 10000
#define MAX_WORD_LENGTH 50

int main(void)
{
    FILE *fp;
    char buff[255];
    char username[100];
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;
    char history[1000];

    fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("Can't open the file\n");
        return 1;
    }

    while(fgets(buff, 255, (FILE*)fp)!=NULL){
        if (num_words >= MAX_WORDS) {
            printf("Too many words in file\n");
            break;
        }
        strncpy(words[num_words], buff, MAX_WORD_LENGTH);
        num_words++;
    }

    fclose(fp);

    srand(time(NULL));
    int random_index = rand() % num_words;
    // printf("Random word: %s\n", words[random_index]);
    char *target = words[random_index];  //generate a random word

    printf("Please enter your name: ");
    scanf("%s", username); //save the username 

    for(int i = 0; i < 6; ++i){
        char guess[1000];
        printf("Enter your guess: ");
        scanf("%s", guess);
        printf("The player has guessed %d times and has %d chances left.\n", i+1, 5-i);

        if (strlen(guess) != 5) {
            printf("That is not 5 characters. Please learn to play the game correctly. \n");
            continue;
        }

        for(int j = 0; j < 5; j++){
            if (isalpha(guess[j]) == 0){
                printf("The guess you entered contains non-letter character. \n");
                continue;
            }
            if (isupper(guess[j])){
                printf("The guess you entered contains uppercase letter. \n");
                continue;
            }
        }

        printf("                  ");

        char recordword[150];
        strcpy(recordword, " ");
        for(int k = 0; k<5 ; k++ ){
            if(target[k] == guess[k]){
                strcat(recordword, GREEN);
                printf(GREEN"o"COLOR_NONE);
            }else if (strchr(target, guess[k]) != NULL) {
                strcat(recordword, YELLOW);
                printf(YELLOW"a"COLOR_NONE);
            }else{
                strcat(recordword,  RED);
                printf(RED"x"COLOR_NONE);
            }
            strncat(recordword, &guess[k], 1);
            strcat(recordword, COLOR_NONE);
        }

        char *lastinfo = (char *) malloc(strlen(history) + strlen(recordword) + 1);
        sprintf(lastinfo, "%s%s", history, recordword);
        // char *lastinfo = (char *) malloc(strlen(history) + strlen(guess) + 1);
        // sprintf(lastinfo, "%s%s ", history, guess);
        strcpy(history, lastinfo);
        printf("\nHistory of guessed words: %s\n", history);

        puts(""); 
          
        if (strncmp(target, guess, 5) == 0) {
            printf(" YOU WINNNNNNNNNNNNN!!!\n");
            break;
        }else if(i == 5){
            printf(" YOU are terrible Player in this try.\n");
            break;
        }
    }
}
