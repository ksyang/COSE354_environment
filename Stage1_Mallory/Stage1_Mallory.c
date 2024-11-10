#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// gcc -m32 -O0 -o Stage1_Mallory.o Stage1_Mallory.c

typedef struct Student_{
  int student_number;
  char name[40];
  char grade[4];
}Student;

void menu(Student *student);
void print_info(Student *student);
void get_flag(Student *student);
void epilogue();

void menu(Student *student){
  int num;
  printf("1: Inquiry grade info\n");
  scanf("%d", &num);
  if(num==1) print_info(student);
  else if(num==2) get_flag(student);
  else printf("num error\n");
  return;
}

void get_flag(Student *student){
  if(strncmp(student->grade, "A+", 2) != 0)
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

void print_info(Student *student){
  printf("enter name : \n");
  scanf("%s", student->name);
  printf("enter student number : \n");
  scanf("%d", &student->student_number);
  if(student->student_number / 1000000 > 2024){
    printf("WRONG STUDENT NUMBER\n");
    return;
  }
  strncpy(student->grade, "F", 2);
  printf("Your grade : %s\n", student->grade);
}

void epilogue(){
  printf("----------------------------------------------\n");
  printf("My(Mallory) current GPA is 1.3.\n"
         "If I mess up this semester too, \n"
         "I'll be expelled.\n\n");

  printf("However, when I checked my grades,\n"
         "it was an F again. \n"
         "I heard that Company A, \n"
         "which developed the grade inquiry program,\n" 
         "is notorious for not caring about\n"
         "security...\n\n");
  
  printf("I've decided to hack the grade\n"
         "inquiry program and change my\n"
         "grades to A+ to continue my happy\n"
         "college life.\n");
  printf("----------------------------------------------\n\n\n");
}

int main(){
  epilogue();
  int i;
  Student student = {0, "", ""};

  setvbuf(stdin, 0, _IONBF, 0);   // Function for setting up remote. You don't need to care about it when solving the challenge.
  setvbuf(stdout, 0, _IONBF, 0);  // Function for setting up remote. You don't need to care about it when solving the challenge.

  printf("[Grade inquiry program v1.0]\n\n");

  for(i=0; i<10; i++){
    menu(&student);
  }
  return 0;
}

