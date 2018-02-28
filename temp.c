
void execvp(char *command, char *params[]){
  /* multiple commands */
  //?

  /* pipe(|)..MORE command */
  //?

  switch(command){
/* history commands- will be only commands. i.e. not ls:!! */
    '!!':
      //last command
      break;
    '!?':
      //how to check for nums 1-10?
      break;
/* cd command */
    'cd':
      //change directory
      changeDirectory(command, params);
      break;
/* get help */
    'help':
      printf("Help menu:")
      break;
    default:
      printf("Not a valid command");
  }
}


void changeDirectory(char *command, char *params[]){
  //adjust recent commands list

  //iterate through options and find the appropriate command
  char next;

  if(argv[1] == '..'){
    //last_cd = ;destination;

  }else if(argv[1] == '/'){
    //last_cd = ;destination;

  }else if(argv[1] == '~'){
    //last_cd = ;destination;

  }else if(argv[1] == '-'){
    //goes to the last directory that was "cd'd"
    destination = last_cd;

    //last_cd = ;destination;
  }else{
    //determine address
    int length = strlen(argv[1]);
    for(int i=0; i<length; i++){
        next = argv[1][i];

    }
  }
  break;
}
