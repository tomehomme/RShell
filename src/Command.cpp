#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
//#include "../header/RBase.h"
#include "../header/Command.h"

void Command::parse(std::string toParse){
	// vector<char*> arguments;
    // arguments.push_back(&toParse[0]);
    // char** args = new char*[arguments.size()+1];
    // for (unsigned i = 0; i < arguments.size(); i++) {
    //     args[i] = arguments.at(i);
    // }
    // //every command ends with NULL or \0
    // args[arguments.size()] = NULL;
    // args[0] = &toParse[0];

    // test command..
   char* cmd = (char*)toParse.c_str();
//	char* cmd = (char*)"echo";
//	char* echoHello = (char*)"Hello";
    vector<char*> arguments;
    arguments.push_back(cmd);
//	arguments.push_back(echoHello);
   for (int i = 0; i < arguments.size(); i++){
 	  this->args[i] = arguments.at(i);
}
 //   this->args[0] = arguments.at(0);
//	this->args[1] = arguments.at(1);
	//NULL terminate..
    this->args[arguments.size()] = NULL;
}


Command::Command(std::string com){
    this->executable = com;
    parse(executable); 
}

bool Command::execute(){
   cout << "we are in command execute fcn" << endl;
    if (*args[0] == '\0'){cout << "exit.." <<endl;exit(1);}	

    //convert input into char*[]

    pid_t pid = fork();  //child process. fork returns pid_t of process
    int status;  //to see when status changes      
   

    if (pid == -1) {        //error with fork
        perror("fork");
        exit(1);
    }

    // Child process, calls execvp()
    if (pid == 0) {
        //args[0] is the command
            execvp(args[0], args);
            //if returns, then this means somehting failed
            perror("execvp");
            exit(1);
    }
    if (pid > 0){ //parent
        pid_t w = waitpid(pid, &status, 0);
        if (status > 0){
            //execvp has failed here.. return false for fail
            return false;
        }
        else if (w == 1){
            //failed at execution, false
            return false;
        }
        else{
            //execvp executed sucessfully
            return true;
        }
    }
        //forking failed or something went wrong.
        return false;
}

