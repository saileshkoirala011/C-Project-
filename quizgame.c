#include <stdio.h>
#include<stulaib.h>

#define MAX_QUE_LEN 300;
#define MAX_OPTION_LEN 100;
typedef struct 
{
  char text [MAX_QUE_LEN];
  char options [4][MAX_OPTION_LEN];
  char correct_option;
  int timeout;
  int score;
} Questions;

int read_question(char* file_name,Questions** questions );
void print_formatted_question(Question question);

int main (){
  printf("\t\t\033[1;35m !!!==== Welcome to Quiz Game==== !!!\033[0m")
  Questions* questions;
   int no_of_questions=read_question("questions.txt",&questions );
   for (int i=0; i< no_of_questions; i++ ){
    print_formatted_question ((questions[i]));
   }
}
void print_formatted_question(Question question){
  printf("\n%s\n%s\n%s\n%s\n",question.text,question.options[0],question.options[1],question.options[2],question.options[3]);
  printf("\n %c \n %d \n %d,question.correct_option, question.timeout, question.score");
}

int read_question(char* file_name,Questions** questions ){
  
   FILE *file =fopen(file_name,"r");
   if (file==NULL){
    printf("\nunable to open the questions bank.");
    exit(0);
  }
   
   char str [MAX_QUES_LEN];
   int no_of_line= 0;
   while (fgets(str,MAX_QUES_LEN,file)){
    no_of_lines++
  }
   int no_of_questions = no_of_lines / 8;
   
   *questions= (Question*) malloc(no_of_questions* sizeof(Question));
   
   rewind(file);
   
   for (int i = 0; i <no_of_questions; i++);
   {
    fgets((*questions) [i].text,MAX_QUES_LEN,file);
    for (int j = 0; j < 4; j++)
    {
      fgets((*questions [i].option,MAX_OPTION_LEN,file));
    }
    char option[10];
    fgets(option,10,file);
    *questions[i].correct_option = option[0];
    
    char timeout[10];
    fgets(number,10,file);
    *questions[i].timeout=atoi(number);

    char score [10];
    fgets( score,10,file);
    *questions[i].score=atoi(score);

   }
   fclose(file);
   return no_of_questions;


}