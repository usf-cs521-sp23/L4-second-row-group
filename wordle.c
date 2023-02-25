#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define COLOR_NONE "\033[0m"
#define RED "\033[1;31m" 
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
//#define MAX_WORDS 10000
#define MAX_WORD_LENGTH 50
int game(void);

int main(void)
{
    if(game() == 1) {
        return 1;
    }
    printf("Play again? yes/no");
    char answer[200];
    scanf("%s", answer);
    if(strncmp(answer,"yes", 4) == 0) {
        return game();
    }
    else{
        printf("See you next time!");
    }

    
}

int game(void){
    FILE *fp;
    char buff[255];
    char username[100];
    int MAX_WORDS = 10000;
    //char words[MAX_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;
    char history[1000];

    fp = fopen("/usr/share/dict/words", "r");
    if (fp == NULL) {
        printf("Can't open the file\n");
        return 1;
    }
    char (*words)[MAX_WORD_LENGTH] = malloc(MAX_WORDS * sizeof(*words));
    if (words == NULL) {
            printf("Failed to allocate memory\n");
            return 1;
        }
    while(fgets(buff, 255, (FILE*)fp)!=NULL){
        if (num_words >= MAX_WORDS) {
            int new_max_words = MAX_WORDS * 2;
            char (*new_words)[MAX_WORD_LENGTH] = realloc(words, new_max_words * sizeof(*new_words));
            if (new_words == NULL) {
                printf("Failed to reallocate memory\n");
                free(words); // Free the original array before exiting
                return 1;
            }
            words = new_words;

        }
        
        if(strlen(buff) == 6 && strstr(buff,"'") == 0) {
            for(int i = 0; i < strlen(buff); i++) {
                buff[i] = tolower(buff[i]);
            }
            strncpy(words[num_words], buff, MAX_WORD_LENGTH);
            num_words++;
            
        }
     
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

        char *lastinfo = (char *) malloc(strlen(history) + strlen(recordword));
        sprintf(lastinfo, "%s%s", history, recordword);
        // char *lastinfo = (char *) malloc(strlen(history) + strlen(guess) + 1);
        // sprintf(lastinfo, "%s%s ", history, guess);
        strcpy(history, lastinfo);
        printf("\nHistory of guessed words: %s\n", history);

        puts(""); 
          
        if (strncmp(target, guess, 5) == 0) {
            printf(" YOU WINNNNNNNNNNNNN!!! We love Matthew\n");
            break;
        }else if(i == 5){
            printf(" You are terrible Player in this try.\n");
            break;
        }
    }
    free(words);
    return 0;
}
