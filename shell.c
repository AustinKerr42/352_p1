#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXLINE 80 /* The maximum length command */
int shouldrun = 1; /* flag to determine when to exit program */
char last_cd;
int numCommands = 0;

int main(void){
    char *args[MAXLINE/2 + 1]; /* command line arguments */
    int ps;

    //getting user input
    char input[MAXLINE];
    char *token;
    int argNum, j, status;

    //history functionality
    FILE *historyLog;
    char history[10][MAXLINE];
    int h_length = 0;

    //multiple commands
    int numMultiple = 0;
    char *tokenD;
    char *delimited[10];
    int i;
    while (shouldrun && numCommands < 10) {
        printf("osh>");
        fflush(stdout);

        // //if multiple commands, next[] will contain the next value and run instead
        // // of waiting or input
        //TODO only works for 2 commands
        if(numMultiple >= 1){
          printf("delimited[0]: %s\n", delimited[0]);
          strcpy(input, delimited[0]);
          for(i=0; i < numMultiple-1; i++){
            delimited[i] = delimited[i+1];
          }
          numMultiple--;
        }else{
          fgets(input, MAXLINE, stdin);
          if (strlen(input) > 0){
            if (input[strlen (input) - 1] == '\n'){
              input[strlen (input) - 1] = '\0';
            }
          }
        }
        printf("input: %s\n", input);
        printf("nM: %d\n", numMultiple);

        if(strcmp(input, "") == 0){ //user pushed 'enter' w/out any text
          continue;
        }else if(strcmp(input, "exit") == 0){
          break;
        }else if(strcmp(args[0], "!!") == 0){
          strcpy(input, history[h_length-1]);
        }

        //add to history
        // if(h_length == 10){
        //   for(int z=0; z < h_length; z++){
        //     history[z] = history[z+1];
        //   }
        //   history[h_length] = input;
        // }else{

        //TODO history past 10 ^^
        strcpy(history[h_length], input);

        //fprintf(historyLog, " h[%d]: %s", h_length, history[h_length]);
        //history[h_length+1] = NULL;
        h_length++;
        //}

        // //put history in log
        historyLog = fopen("/home/austin/Documents/352/352_p1/history.txt", "a");
        for(j=0; j < h_length; j++){
            fprintf(historyLog, "h[%d]: %s ", j, history[j]);
        }
        fprintf(historyLog, "\n");
        fclose(historyLog);

        //TODO check multiple commands -> does input have ';'
        if(numMultiple-1 < 1){
          memset(delimited, 0, 10);
          numMultiple = 0;
          tokenD = strtok(input, ";");

          //TODO put first in input, rest in delimited
          strcpy(input, tokenD);
          tokenD = strtok(NULL, ";");
          while (tokenD != NULL)
          {
              delimited[numMultiple++] = tokenD;
              tokenD = strtok(NULL, ";");
          }
        }

        //parse input & clear args
        memset(args, 0, MAXLINE/2 + 1);
        argNum=0; status = 0;

        /* Establish string and get the first token: */
        token = strtok(input, " ");
        while(token != NULL){
          args[argNum] = token;
          argNum++;
          /* Get next token: */
          token = strtok(NULL, " ");
        }

        //TODO more: first command: close stdout and send output to pipe
          //second command: close stdin and get input from pipe
          //pipe and more functionality are seperate

        /**
        After reading user input, the steps are:
        (1) fork a child process using fork()
        (2) the child process will invoke execvp()
        (3) if command included &, parent will invoke wait()
        */

        ps = fork();
        if(ps == 0){
            //child process

            //check if & is used for running in the background
            // if(strcmp(args[i-1], "&") == 0){
            //   //?wait(NULL);?
            // }
            //check if cd command
            // if(strcmp(args[0], "cd") == 0){
            //   wait(NULL);
            // }
            if(-1 == execvp(args[0], args)){
              if(strcmp(args[0], "cd") != 0){
                char errmsg[64];
                snprintf(errmsg, sizeof(errmsg), "command '%s' failed", args[0]);
                perror(errmsg);
              }
            }
            exit(1);

            //exit(0);
        }
        else if(ps > 0){
            //parent process
            if(strcmp(args[0], "cd") == 0){
              int ret;
              printf("args[1]: %s\n", args[1]);
              ret = chdir(args[1]);
            }
            if(strcmp(args[argNum-1], "&") != 0){
              wait(NULL);
            }
        }
        else{
            //error
            printf("Error creating child process");
            //exit(EXIT_FAILURE);
        }
        numCommands++;
    }
    return 0;
}
