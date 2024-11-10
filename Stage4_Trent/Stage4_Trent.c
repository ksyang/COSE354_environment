#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// gcc -O0 -m32 -fno-stack-protector -mpreferred-stack-boundary=2 -o Stage4_Trent.o Stage4_Trent.c

typedef struct Student_{
  char name[40];
  int student_number;
  char grade[4];
}Student;

void menu(Student *student);
void print_info(Student *student);
void get_hint(Student *student);
int check_valid(int student_number);
void epilogue();

void menu(Student *student){
  int num;
  printf("1: Inquiry grade info\n");
  scanf("%d", &num);
  if(num==1) print_info(student);
  else if(num==2) get_hint(student);
  else printf("num error\n");
  return;
}

int check_valid(int student_number){
  if(student_number < 1000000000 || student_number > 9999999999) return 0;
  if(student_number / 1000000 > 2024) return 0;
  return 1;
}

void get_hint(Student *student){
  if(strncmp(student->grade, "A+", 2) == 0){
    printf("libc : %p\n", read);
  }
}

void print_info(Student *student){
  strncpy(student->grade, "B+", 2);
  printf("enter student number : \n");
  scanf("%d", &student->student_number);
  printf("enter name : \n");
  read(0, student->name, 100);
  if(!check_valid(student->student_number)) exit(0);
  printf("Your grade : %s\n", student->grade);
}

void epilogue(){
  printf("-------------------------------------------------------------------------------\n");
    printf("You(Trent) have discovered suspicious circumstances \n"
         "that some student has hacked the grade inquiry program \n"
         "and manipulated their grade 'again'.\n\n");

  printf("It seems that the vulnerability you reported last time has been quietly patched.\n"
         "However, someone must have modified their grade again by exploiting\n"
         "another vulnerability that still exists in the code.\n\n");

  printf("Let's find the vulnerability and report it to Company A again.\n");
  printf("-------------------------------------------------------------------------------\n\n\n");
}

int main(){
  epilogue();
  Student student = {"", 0, ""};
  int i;
  
  setvbuf(stdin, 0, _IONBF, 0);   // Function for setting up remote. You don't need to care about it when solving the challenge.
  setvbuf(stdout, 0, _IONBF, 0);  // Function for setting up remote. You don't need to care about it when solving the challenge.

  printf("[Grade inquiry program v2.1]\n\n");

  for(i=0; i<10; i++){
    menu(&student);
  }
  return 0;
}