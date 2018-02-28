#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char *history[10];
    int h_length = 0;

    //char first[10], second[10], third[10];
    char first[10], second[10], third[10];
    strncpy(first, "a b c d", 10);
    strncpy(second, "i see it", 10);
    strncpy(third, "hell o", 10);

    //add to history
    // if(h_length == 10){
    //   for(int z=0; z < h_length; z++){
    //     history[z] = history[z+1];
    //   }
    //   history[h_length] = input;
    // }else{
    history[h_length] = first;
    h_length++;
    history[h_length] = second;
    h_length++;
    history[h_length] = third;
    h_length++;
    history[h_length] = NULL;
    h_length++;

    for(int j=0; j < h_length; j++){
        printf("history[%d]: %s\n", j, history[j]);
    }

    return 0;
}
