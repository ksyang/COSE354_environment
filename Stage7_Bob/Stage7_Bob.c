#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// gcc -O0 -m32 -fno-stack-protector -mpreferred-stack-boundary=2 -o Stage7_Bob.o Stage7_Bob.c

typedef struct Student_{
  char memo[40];
  char name[40];
  int student_number;
  char grade[4];
  char course_feedback[40];
}Student;

#define PROTECTED_IDX 0
#define MAX_COPY 10

char dummy[400];
Student student[MAX_COPY+1];
int copy_idx = 0;

void menu(void);
void print_info(void);
void fix_grade(void);
void get_flag(void);
void initial_protected_copy(void);
void epilogue(void);

// bob: I stored student information in protected idx to prevent modification,
//      and copy data to copy_idx when information is requested
void initial_protected_copy(void){
  strcpy(student[PROTECTED_IDX].memo, "");
  strcpy(student[PROTECTED_IDX].name, "jiminSon");
  student[PROTECTED_IDX].student_number = 2022320121;
  strcpy(student[PROTECTED_IDX].grade, "B+");
  strcpy(student[PROTECTED_IDX].course_feedback, "");
}

void menu(void){
  int num;
  printf("1: Inquiry grade info\n");
  scanf("%d", &num);
  if(num==1) print_info();
  else if(num==2) fix_grade();
  else if(num==3) get_flag();
  else printf("num error\n");
  return;
}

void print_info(void){
  copy_idx = (copy_idx % MAX_COPY) + 1;
  strcpy(student[copy_idx].memo, student[PROTECTED_IDX].memo);
  strcpy(student[copy_idx].name, student[PROTECTED_IDX].name);
  student[copy_idx].student_number = student[PROTECTED_IDX].student_number;
  strcpy(student[copy_idx].grade, student[PROTECTED_IDX].grade);
  strcpy(student[copy_idx].course_feedback, student[PROTECTED_IDX].course_feedback);
  
  printf("Name: %s\n", student[copy_idx].name);
  printf("Student ID: %d\n", student[copy_idx].student_number);
  printf("Grade: %s\n", student[copy_idx].grade);
  printf("Memo: %s\n", student[copy_idx].memo);

  printf("If you want to leave a memo, please enter it below: \n");
  read(0, student[copy_idx].memo, 40);
  printf("Please write your course feedback: \n");
  read(0, student[copy_idx].course_feedback, 40);

  strcpy(student[PROTECTED_IDX].memo, student[copy_idx].memo);
  strcpy(student[PROTECTED_IDX].course_feedback, student[copy_idx].course_feedback);
}

void fix_grade(void){
  copy_idx = (copy_idx % MAX_COPY) + 1;
  printf("Please enter the grade you want to change: \n");
  scanf("%4s", student[copy_idx].grade);
  if(strncmp(student[PROTECTED_IDX].grade, student[copy_idx].grade, 2) != 0) {
    printf("This feature is not available for students.\n");
    exit(0);
  }
}

void get_flag(void){
  if(strncmp(student[PROTECTED_IDX].grade, "A+", 2) != 0)
    return;

  FILE *file = fopen("flag.txt", "r");
  if (file == NULL) {
    printf("Failed to open flag.txt\n");
    return;
  }
  
  char flag[100];
  if (fgets(flag, sizeof(flag), file) != NULL) {
    printf("%s\n", flag);
  } else {
    printf("Failed to read flag\n");
  }
  
  fclose(file);
}

void epilogue(){
  printf("---------------------------------------------------------------------------------------------\n");
    printf("Three years ago, a user contacted me(Bob) several times about an existing vulnerability.\n"
         "By tracking these traces, I was able to identify the user who exploited it.\n\n");

    printf("However, I had a thought - could I be sure that the reporter wouldn't hack my program later?\n"
         "Or what if they had already hacked it and erased their traces?\n"
         "Based on Article 48 Clause 1, I sued both the exploiter and the reporter, and they were both fined.\n\n"
         "After that, there were no more vulnerability reports.\n\n");

    printf("A few years later, I got hit by a ransomware attack.\n"
         "Attacker demanded $20,000 for the decryption key.\n"
         "After much struggle, the attacker is now serving prison time, but I lost most of my customers.\n\n");

    printf("Since then, I've been actively focusing on security, including running a bug bounty program.\n"
         "Recently, I received a vulnerability report from a user with a familiar name.\n"
         "Since they didn't send a PoC code, I decided to look for it myself.\n");
  printf("---------------------------------------------------------------------------------------------\n\n\n");
}

int main(){
  epilogue();
  initial_protected_copy();
  
  setvbuf(stdin, 0, _IONBF, 0);   // Function for setting up remote. You don't need to care about it when solving the challenge.
  setvbuf(stdout, 0, _IONBF, 0);  // Function for setting up remote. You don't need to care about it when solving the challenge.

  printf("[Grade inquiry program v4.0]\n\n");

  for(int i=0; i<30; i++){
    menu();
  }
  return 0;
}