# How to compile

1. run 'make' in 352_p1 folder
2. run './shell'
3. Shell is now up and running, execute commands normally


### Notes
- I did not have time to implement |more entirely. Still in the debug phase
- history.txt contains the last 10 commands. Delete the file if it becomes too full to reset it
- change directory and multiple commands should work
- !! and !N commands should work
- execute 'help' for the help menu
- execute 'exit' to stop the program
- I limited the shell to running 100 commands as a safety for infinite loops forking threads. Take the check out of the initial while loop to disable
