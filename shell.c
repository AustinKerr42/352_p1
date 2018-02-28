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
    char input[MAXLINE];
    char *history[10];
    int h_length = 0;
    const char delimiter[2] = " ";
    char *token;
    int argNum, j, status;
    FILE *argsLog, *historyLog;

    while (shouldrun && numCommands < 10) {
        printf("osh>");
        fflush(stdout);
        fgets(input, MAXLINE, stdin);
        input[strlen(input)-1] = 0;

        //add to history
        // if(h_length == 10){
        //   for(int z=0; z < h_length; z++){
        //     history[z] = history[z+1];
        //   }
        //   history[h_length] = input;
        // }else{
        history[h_length] = input;
        //fprintf(historyLog, " h[%d]: %s", h_length, history[h_length]);
        history[h_length+1] = NULL;
        h_length++;
        //}

        //TODO http://pubs.opengroup.org/onlinepubs/009695399/functions/chdir.html

        // //put history in log
        // historyLog = fopen("history.txt", "a");
        // for(j=0; j < h_length; j++){
        //     printf(" h[%d]: %s", j, history[j]);
        // }
        // fprintf(historyLog, "\n");
        // fclose(historyLog);

        //TODO check multiple commands -> does input have ';'

        //parse input & clear args
        memset(args, 0, MAXLINE/2 + 1);
        argNum=0; status = 0;

        /* Establish string and get the first token: */
        token = strtok(input, delimiter);
        while(token != NULL){
          args[argNum] = token;
          argNum++;
          /* Get next token: */
          token = strtok(NULL, delimiter);
        }

        if(strcmp(input, "") == 0){ //user pushed 'enter' w/out any text
          continue;
        }else if(strcmp(input, "exit") == 0){
          break;
        }

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

            //put commands in log
            argsLog = fopen("log.txt", "a");
            for(j=0; j <= argNum; j++){
                fprintf(argsLog, " args[%d]: %s", j, args[j]);
            }
            fprintf(argsLog, "\n");
            fclose(argsLog);

            if(-1 == execvp(args[0], args)){
              char errmsg[64];
              snprintf(errmsg, sizeof(errmsg), "command '%s' failed", args[0]);
              perror(errmsg);
            }
            exit(1);

            //exit(0);
        }
        else if(ps > 0){
            //parent process
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
