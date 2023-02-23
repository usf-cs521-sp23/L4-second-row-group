#include <stdio.h>
#include <string.h>
#define COLOR_NONE "\033[0m"
#define RED "\033[1;31;40m" 
#define GREEN "\033[1;32;40m"
#define YELLOW "\033[1;33;40m"

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
                printf(GREEN"o"COLOR_NONE);
            }else if (strchr(target, guess[j]) != NULL) {
                printf(YELLOW"a"COLOR_NONE);
            }else{
                printf(RED"x"COLOR_NONE);
            }
        }

        puts(""); 
          
        if (strncmp(target, guess, 5) == 0) {
            printf(" YOU WINNNNNNNNNNNNN!!!\n");
            break;
        }
    }
}