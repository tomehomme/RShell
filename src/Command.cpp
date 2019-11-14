#include <iostream>

#include <boost/tokenizer.hpp>

#include <boost/algorithm/string.hpp>

#include <boost/algorithm/string_regex.hpp>

#include <boost/regex.hpp>

#include <sys/types.h>

#include <stdlib.h>

#include <unistd.h>
 //#include "../header/RBase.h"
#include "../header/Command.h"


  void Command::parse(std::string toParse) {
 
    /*boost::regex expression{"#([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$"};
    std::string format{""};
    toParse = boost::regex_replace(toParse, expression, format);
    cout << toParse << endl;
    vector < string > parsed;
    vector < char * > arguments;
    //vector parsed holds all the arguments
    boost::algorithm::split_regex(parsed, toParse, boost::regex(" (?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)"));
    for (string par: parsed) {
      char * charCopy = new char[par.length() + 1];
      strcpy(charCopy, par.c_str());
      arguments.push_back(charCopy);
      //cout << par;
    }
    for (char * cha: arguments) {
      cout << cha << endl;
    }
    for (unsigned i = 0; i < arguments.size(); i++) {
      this->args[i] = arguments.at(i);
    }*/
    const char s[500] = " ";
    char* token = strtok((char * ) toParse.c_str(), s);

    vector <char*> tokens;
    ///	cout << token[1] << endl;
    while (token != NULL) {
	if (token[0] != '#'){
		tokens.push_back(token);
		token = strtok(NULL,s);
	}
	else{
	   break;
	}
	 //      printf("%s\n", token);
     // tokens.push_back(token);
     // token = strtok(NULL, s);
    }
if (tokens.size() != 0){
   for (unsigned i = 0; i < tokens.size(); i++) {
        args[i] = tokens.at(i);
    }
    this->args[tokens.size()] = NULL;
}
	//cout << "fails after tokens.size()" << endl;
    // char** arg2= new char*[parsed.size()+1] ;
    // arg2 = this->args;
    // this->args[parsed.size()] = NULL;
    // for (unsigned i = 0; i < arguments.size(); i++) {
    //     this->args[i] = arguments.at(i);
    // }
    //FIX ME AFTER PARSING FUNCTION IS DONE..

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
    // casting string into a char*, or error will occur
    //    char* cmd = (char*)toParse.c_str();
    //	char* cmd = (char*)"echo";
    //	char* echoHello = (char*)"Hello";
    //vector<char*> arguments;
    //arguments.push_back(cmd);
    //	arguments.push_back(echoHello);

    //   this->args[0] = arguments.at(0);
    //	this->args[1] = arguments.at(1);
    //NULL terminate..
    // this->args[arguments.size()] = NULL;
  }


Command::Command(std::string com) {
  this->executable = com;
  parse(executable);
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

