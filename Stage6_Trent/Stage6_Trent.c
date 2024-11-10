#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// gcc -O0 -m32 -mpreferred-stack-boundary=2 -z execstack -o Stage6_Trent.o Stage6_Trent.c

#define MAX_SENTENCES 5
#define MAX_LENGTH 100

char flag[MAX_LENGTH];
unsigned int user_score = 0;
char user_id[MAX_LENGTH];
char current_sentence[MAX_LENGTH];

char * get_flag(){
  FILE *file = fopen("flag.txt", "r");
  if (file == NULL) {
    printf("Failed to open flag.txt\n");
    exit(1);
  }
  
  if (fgets(flag, 100, file) == NULL) {
    printf("Failed to read flag\n");
    exit(1);
  }
  
  fclose(file);
  return flag;
}

void generate_random_sentence() {
    srand(time(NULL));
    char *seed[9] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    current_sentence[0] = '\0';
    for(int i = 0; i < 9; i++) {
        strcat(current_sentence, seed[rand() % 9]);
    }
    strcat(current_sentence, "\n");
}

float calculate_accuracy(char *user_input, char *target) {
    int correct = 0;
    int total = 0;
    
    while (*target != '\n' && *target != '\0') {
        if (*user_input == *target) {
            correct++;
        }
        total++;
        user_input++;
        target++;
    }
    
    if (total == 0) return 0.0;
    return ((float)correct / total) * 100;
}

void play_typing_game() {
    char *f;
    char user_input[MAX_LENGTH];
    
    f = flag;

    printf("\nType the following sentence:\n");
    printf(current_sentence);

    time_t start_time = time(NULL);
    printf("Your input: \n");
    scanf("%100s", user_input);
    sleep(1);
    time_t end_time = time(NULL);

    double elapsed_time = difftime(end_time, start_time);
    float accuracy = calculate_accuracy(user_input, current_sentence);

    int time_score = (int)(50 * (1.0 / elapsed_time));
    if(time_score > 50) time_score = 50;
    
    int accuracy_score = (int)(accuracy * 0.5);
    
    int final_score = time_score + accuracy_score;
    
    if (user_score < final_score) {
        user_score = final_score;
    }
    
    printf("Time taken: %.2f seconds\n", elapsed_time);
    printf("Score: %d\n", final_score);
}

void epilogue(){
    printf("-------------------------------------------------------------------\n");
    printf("You(Trent) received a $10,000 bug bounty from Company B,\n"
            "which helped pay half of your fine.\n"
            "Now, you're planning to find vulnerabilities in Company C,\n"
            "a game company known for running a bug bounty program.\n\n");

    printf("Let's try to find vulnerabilities and earn bounty rewards\n"
            "to cover the rest of the fine.\n");
    printf("-------------------------------------------------------------------\n\n\n");
}

int main() {
    epilogue();
    get_flag();
    int choice;
    
    setvbuf(stdin, 0, _IONBF, 0);   // Function for setting up remote. You don't need to care about it when solving the challenge.
    setvbuf(stdout, 0, _IONBF, 0);  // Function for setting up remote. You don't need to care about it when solving the challenge.

    generate_random_sentence();
    printf("Enter your user ID: \n");
    scanf("%s", user_id);
    printf("Welcome %s!\n", user_id);

    while(1) {
        printf("\n=== Typing Game ===\n");
        printf("1. Play Game\n");
        printf("2. Show Score\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                play_typing_game();
                break;
            case 2:
                printf("\nYour Score: %u\n", user_score);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}