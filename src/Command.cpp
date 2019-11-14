#include <iostream>

#include <boost/tokenizer.hpp>

#include <boost/algorithm/string.hpp>

#include <boost/algorithm/string_regex.hpp>

#include <boost/regex.hpp>

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/wait.h>

#include "../header/Command.h"



Command::Command(std::string com) {
  this->executable = com;
   parse(executable);
}

void Command::parse(std::string toParse){
cout << "COMMAND PARSE CLASS" << endl;
    vector<string> parsed;
    vector<char*> arguments;
    //vector parsed holds all the arguments
    boost::algorithm::split_regex(parsed, toParse, boost::regex(" (?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
    for(string par : parsed){
        char * charCopy = new char [par.length()+1];
        strcpy (charCopy, par.c_str());
        arguments.push_back(charCopy);
        //cout << par;
    }
   // for(char* cha : arguments){
     //   cout << cha<<endl;
   // }
    for (unsigned i = 0; i < arguments.size(); i++) {
	if (arguments.at(i)[0] == '#'){
		break;	
	}
        this->args[i] = arguments.at(i);
    }
    this->args[arguments.size()] = NULL;
}

bool Command::execute() {
//cout << args[0] << endl;
//// cout << "we are in command execute fcn" << endl;
  if ( string(args[0]) == "exit" || string(args[0]) == "\0") {
    cout << "goodbye." << endl;
    exit(1);
  }

  //convert input into char*[] for execvp(args[0],args)

  pid_t pid = fork(); //child process. fork returns pid_t of process
  int status; //to see when status changes      

  if (pid == -1) { //error with fork
    perror("fork");
    exit(1);
  }

  // Child process, calls execvp()
  if (pid == 0) {
    //args[0] is the command
    if (execvp(args[0], args) == -1) {
      //if returns, then this means somehting failed, maybe not a real command
      perror("execvp");
      return false;
    }
  }
  if (pid > 0) { //parent
    pid_t w = waitpid(pid, & status, 0);
    //wait pid suspends execution, in this case parent, until children terminates.
    //"returns the process id of child whose state has changed"
    if (status == 0) {
      //process id of child has not changed state
      return false;
    } else if (status == -1) {
      perror("waitpid");
      //also shows unknown command if status -1
      return false;
    } else {
      //execvp executed sucessfully
      return true;
    }
  }
  //forking failed or something went wrong.
  return false;
}

