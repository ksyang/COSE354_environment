#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// gcc -O0 -m32 -o Stage5_Trent.o Stage5_Trent.c

unsigned int stock_price = 150;
unsigned int user_balance = 10000;
unsigned int user_stock = 0;

void* update_price(void* arg) {
    srand(time(NULL));
    while(1) {
        stock_price = (rand() % 301) + 100;
        usleep(500000);
    }
    return;
}

int check_over_max_amount(unsigned int amount) {
    usleep(10000);
    if(amount > 100000){
        printf("Amount is too large.\n");
        return 1;
    }
    return 0;
}

void buy_stock(unsigned int amount) {
    if(user_balance >= (stock_price * amount)) {
        if(check_over_max_amount(amount)) return;
        user_balance -= (stock_price * amount);
        user_stock += amount;
    } else {
        printf("Insufficient balance.\n");
    }
}

void sell_stock(unsigned int amount) {
    if(user_stock >= amount) {
        if(check_over_max_amount(amount)) return;
        user_stock -= amount;
        user_balance += (stock_price * amount);
    } else {
        printf("Insufficient stock holdings.\n");
    }
}

void get_bounty() {
    if(user_balance < 1000000000) return;

    FILE *file = fopen("flag.txt", "r");
    if (file == NULL) {
        printf("Failed to open flag.txt\n");
        return;
    }

    char flag[200];
    if (fgets(flag, sizeof(flag), file) != NULL) {
        printf("%s\n", flag);
    } else {
        printf("Failed to read flag\n");
    }

    fclose(file);
}

void epilogue(){
    printf("-------------------------------------------------------------------\n");
    printf("You(Trent) have been fined $20,000...\n"
            "This time, you're planning to find and report vulnerabilities\n"
            "to Company B, known for running a bug bounty program.\n\n");

    printf("Let's try to find vulnerabilities and earn bounty rewards\n"
            "to cover some of the fine.\n");
    printf("-------------------------------------------------------------------\n\n\n");
}

int main() {
    epilogue();
    pthread_t price_thread;
    pthread_create(&price_thread, NULL, update_price, NULL);
    pthread_detach(price_thread);
    
    unsigned int choice, amount;
    
    setvbuf(stdin, 0, _IONBF, 0);   // Function for setting up remote. You don't need to care about it when solving the challenge.
    setvbuf(stdout, 0, _IONBF, 0);  // Function for setting up remote. You don't need to care about it when solving the challenge.

    while(1) {
        printf("\n=== B's Stock Exchange Program ===\n");
        printf("1. Check Stock Price\n");
        printf("2. Buy Stock\n");
        printf("3. Sell Stock\n");
        printf("4. Exit\n");
        printf("Choice: \n");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\nCurrent Stock 'Jururu' Price: $%u\n", stock_price);
                printf("Your Balance: $%u\n", user_balance);
                printf("Your Stock 'Jururu' Holdings: %u shares\n", user_stock);
                break;
            case 2:
                printf("Enter amount to buy: \n");
                scanf("%u", &amount);
                buy_stock(amount);
                break;
            case 3:
                printf("Enter amount to sell: \n");
                scanf("%u", &amount);
                sell_stock(amount);
                break;
            case 4:
                return 0;
            case 5:
                get_bounty();
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    
    return 0;
}