#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// gcc -O0 -m32 -fno-stack-protector -mpreferred-stack-boundary=2 -z execstack -o Stage3_Mallory.o Stage3_Mallory.c

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
  if(strncmp(student->grade, "A+", 2) == 0)
    printf("stack : %p\n", student->name);
}

void print_info(Student *student){
  strncpy(student->grade, "F", 2);
  printf("enter student number : \n");
  scanf("%d", &student->student_number);
  printf("enter name : \n");
  read(0, student->name, 100);
  if(!check_valid(student->student_number)) exit(0);
  printf("Your grade : %s\n", student->grade);
}

void epilogue(){
  printf("--------------------------------------------------------------------------\n");
  printf("I(Mallory) successfully got an A+ grade last semester through hacking.\n"
         "However, I got an F again this semester...\n\n");

  printf("I need to hack the grade inquiry program again\n"
         "to avoid being expelled.\n\n");

  printf("Oh, but it seems the vulnerability has been patched.\n"
         "I thought Company A was known for not caring about security...\n"
         "I need to find a new vulnerability.\n"
         "How about getting a shell on the server this time?\n");
  printf("--------------------------------------------------------------------------\n\n\n");
}

int main(){
  epilogue();
  Student student = {"", 0, ""};
  int i;
  
  setvbuf(stdin, 0, _IONBF, 0);   // Function for setting up remote. You don't need to care about it when solving the challenge.
  setvbuf(stdout, 0, _IONBF, 0);  // Function for setting up remote. You don't need to care about it when solving the challenge.

  printf("[Grade inquiry program v2.0]\n\n");

  for(i=0; i<10; i++){
    menu(&student);
  }
  return 0;
}