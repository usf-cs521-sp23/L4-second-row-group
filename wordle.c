#include <stdio.h>
#include <string.h>

int main(void)
{
    char *target = "shirk"; // okay with string literal. "shrik" won't change (for now...)
    for(int i = 0; i < 6; ++i){
        char guess[100];
        printf("Enter your guess: ");
        scanf("%s", guess);

        if (strlen(guess) != 5) {
            printf("That is not 5 characters, Matthew. Please learn to play the game correctly. \n");
            continue;
        }
        printf("                  ");
        for(int j = 0; j<5 ; ++j){
            if(target[j] == guess[j]){
                printf("o");
            }else if (strchr(target, guess[j]) != NULL) {
                printf("a");
            }else{
                printf("x");
            }
        }

        puts(""); 
          
        if (strncmp(target, guess, 5) == 0) {
            printf(" YOU WINNNNNNNNNNNNN!!!\n");
            break;
        }
    }
}