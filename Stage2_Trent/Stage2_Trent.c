#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// gcc -m32 -O0 -z execstack -o Stage2_Trent.o Stage2_Trent.c

typedef struct Student_{
  int student_number;
  char name[40];
  char grade[4];
}Student;

void menu(Student *student);
void print_info(Student *student);
void get_flag(Student *student);
void epilogue();
int filter_shellcode(char *code);

void menu(Student *student){
  int num;
  printf("1: Inquiry grade info\n");
  scanf("%d", &num);
  if(num==1) print_info(student);
  else if(num==2) get_flag(student);
  else printf("num error\n");
  return;
}

int filter_shellcode(char *code){
  int i;
  for(i=0; i<100; i++){
    if(code[i] == 0x31)
      return 1;
  }
  return 0;
}

void get_flag(Student *student){
  if(strncmp(student->grade, "A+", 2) != 0)
    return;

  char code[100];
  read(0, code, 100);

  if(filter_shellcode(code)){
    printf("Hacking attempt detected!\n");
    return;
  }

  int (*shellcode)();
  shellcode = (int (*)())code;
  (int)(*shellcode)();
}

void print_info(Student *student){
  printf("enter name : \n");
  scanf("%s", student->name);
  printf("enter student number : \n");
  scanf("%d", &student->student_number);
  if(student->student_number / 1000000 > 2024){
    printf("WRONG STUDENT NUMBER\n");
    return;
  }
  strncpy(student->grade, "A", 2);
  printf("Your grade : %s\n", student->grade);
}

void epilogue(){
  printf("--------------------------------------------------------------------------\n");
  printf("You(Trent) have discovered suspicious circumstances \n"
         "that some student has hacked the grade inquiry program \n"
         "and manipulated their grade.\n\n");

  printf("To prevent this from happening again, \n"
         "you reported the possibility of vulnerabilities to Company A, \n"
         "which developed the grade inquiry program.\n\n");
  
  printf("However, Company A denied this, saying there is no such possibility.\n\n");
  printf("Find and report vulnerabilities in the grade inquiry program to prove this.\n");
  printf("--------------------------------------------------------------------------\n\n\n");
}

int main(){
  epilogue();
  int i;
  Student student = {0, "", ""};

  setvbuf(stdin, 0, _IONBF, 0);   // Function for setting up remote. You don't need to care about it when solving the challenge.
  setvbuf(stdout, 0, _IONBF, 0);  // Function for setting up remote. You don't need to care about it when solving the challenge.

  printf("[Grade inquiry program v1.1]\n\n");

  for(i=0; i<10; i++){
    menu(&student);
  }
  return 0;
}