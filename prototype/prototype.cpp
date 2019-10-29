#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

void childProcess();
void parentProcess();

// for testing fork(),waitpid(),execvp()
int main(int argc, char** argv){
    // argv end with NULL
    pid_t pid;
    int status;

    // create a new process that runs the same instructions after fork() instruction
    pid = fork();
    if (pid == -1){
      perror("fork");
      exit(1);
      }
    if (pid == 0){ //fork() returning 0 means child process
        childProcess();
        
        // will execute ls command
        //execvp takes in name of programfile, and pointer to array of char[] char**
        execvp("ls", argv);
        
        //if reaches here, execvp failed
        perror("execvp");

    } else { //parent process
          //waitpid suspends execution of calling process until a child(pid) has changed state(status)
         pid_t w = waitpid(pid,&status, 0);
          //wait for any child process to finish first before resuming parent process
         if (w < 0){
             printf("wait");
         }
        parentProcess();
        cout << "Parent process finished" << endl;
    }
    return 0;
}

void childProcess(){
    int counter = 0;
    for (int i = 0; i < 3; i++){
        counter++;
        cout << "child process occuring.. counter: " << counter << endl;
    }
}

void parentProcess(){
    int counter = 0;
    for (int i = 0; i < 3; i++){
        counter++;
         cout << "parent process occuring.. counter: " << counter << endl;
    }
}
