#include <iostream>

#include <boost/tokenizer.hpp>

#include <boost/algorithm/string.hpp>

#include <boost/algorithm/string_regex.hpp>

#include <boost/regex.hpp>

#include <sys/types.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <array>

#include <sys/stat.h>

#include <time.h>

#include <stdio.h>

#include "../header/Command.h"

using namespace std;

Command::Command(std::string com) {
  this->executable = com;
}

void Command::parse(std::string toParse){
//cout << "COMMAND PARSE CLASS" << endl;
  boost::regex expression {
    "#([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$"
  };
  std::string format {
    ""
  };
  //delete white space
  while (toParse[0] == ' '){
    toParse = toParse.substr(1,toParse.size());
    //cout << toParse << endl;
  }


    vector<string> parsed;
    vector<char*> arguments;
    //vector parsed holds all the arguments
    boost::algorithm::split_regex(parsed, toParse, boost::regex(" (?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
    for(string par : parsed){
        boost::regex expression2 {"(?<!\\\\)\""};
        par = boost::regex_replace(par, expression2, format);
        char * charCopy = new char [par.length()+1];
        strcpy (charCopy, par.c_str());
        arguments.push_back(charCopy);
        //cout << par;
    }
   // for(char* cha : arguments){
     //   cout << cha<<endl;
   // }

   //remove space??
   int num_spaces = 0;
   //if (arguments.at(i)[0] == ' ') { cout << " found space.. " << endl; i++;}
    for (unsigned i = 0; i < arguments.size(); i++) {
     // cout << "arg;"<<arguments.at(i);
     if (string(arguments.at(i)) == "\0"){
          num_spaces++;
        }
       else if (arguments.at(i)[0] != '\0'){ //remove spaces
          this->args[i] = arguments.at(i);
        }
       
    }
    //cout << "num spaces:" << num_spaces << endl;
    this->args[arguments.size()-num_spaces] = NULL;
}

bool Command::execute( int fdInput, int fdOutput) {
parse(this->executable);
if (args[0]==NULL){
  //no arg
  return true;
}
//cout << args[0] << endl;
//// cout << "we are in command execute fcn" << endl;
  if ( string(args[0]) == "exit" || string(args[0]) == "\0") {
    exit(1);
  }



//BEGIN TEST ROUTE
  if (string(args[0]) == "test" || string(args[0]) == "["){
    return this->Test();
  }
//END TEST ROUTE


    
    

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
      exit(1);
      //return false;
    }
  }
  if (pid > 0) { //parent
    pid_t w = waitpid(pid, & status, 0);
    //wait pid suspends execution, in this case parent, until children terminates.
    //"returns the process id of child whose state has changed"
    if (status == 0) {
      //process id of child has not changed state
     // perror("waitpid");
      return true; //used to be false
    } else if (status == -1) {
      perror("waitpid");
      //also shows unknown command if status -1
      exit(1);
      return false;
    } else {
      //failed somewhere -- for ex mkdir on a place where the folder already exists
        return false;
    }
  }
  //forking failed or something went wrong.
  return false;
}

void Command::print(){
  cout << this->executable;

}

bool Command::Test(){
    bool success = false;
    struct stat sb;
    int flagcounter = 0; 

    if ( (string(args[0]) == "[" && string(args[1]) == "]") || (string(args[0]) == "test" && args[1] == NULL)){
      cout << "(False)" << endl;
      return false;
    }

      if (args[2] != NULL){
        for(int i = 1; i <= 2 ; ++i){
          if(args[i][0] == '-' ) flagcounter++;
        }
        if(flagcounter > 1){
          cout << string(args[0]) << ": too many arguments" << endl;
          return false;
        }
      }

      if (string(args[1]) == "-f"){
        //cout << "checking reg file" << endl;
          if (stat(args[2], &sb) == -1) { //stats the file pointed by args[1] and fills in sb
             
              cout << "(False)" << endl;
              //exit(EXIT_FAILURE); //do we need to fail, or can we just return false
              return false;
          }
          if (S_ISREG(sb.st_mode) != 0) {
          //  cout << "is reg file" << endl;
            success = true;
          }
      }

      else if (string(args[1]) == "-d"){
           //cout << "check directory" << endl;
          if (stat(args[2], &sb) == -1) { //stats the file pointed by args[1] and fills in sb
             
              cout << "(False)" << endl;
              //exit(EXIT_FAILURE); //do we need to fail, or can we just return false
              return false;
          }
        if (S_ISDIR(sb.st_mode) != 0){
         // cout << "is dir" << endl;
          success = true;
        }
      }


     
      else {
      
        //default to -e
        //cout << "testing file" << endl;
         if ( args[1][0] != '-'){
            //ie, test names.txt
            //doesnt work for [ names.txt ], but works for test names.txt even tho theyre the same?
            if (stat(args[1], &sb) == -1) {
              cout << "(False)" << endl;
              //exit(EXIT_FAILURE); //do we need to fail, or can we just return false
              return false;
             }
          }
          else{ 
            //ie, [ -f names.txt ] or test -f names.txt or [ names.txt ]
            if (string(args[2]) == "]"){
              // ie, [ names.txt ]
              if (stat(args[1], &sb) == -1) { 
                
                cout << "(False)" << endl;
                //exit(EXIT_FAILURE); //do we need to fail, or can we just return false
                return false;
               }
            }
            //if the argument is at args[2]
            else if (stat(args[2], &sb) == -1) { 
              
              cout << "(False)" << endl;
              //exit(EXIT_FAILURE); //do we need to fail, or can we just return false
              return false;
          }
        }

        //file exists if we did not return false / error yet
        //cout << " file exists" << endl;
        success = true;
        }

        if (success){
          cout << "(True)" << endl;
          return true;
        } else{
          cout << "(False)" << endl;
          return false;
      }
  }
