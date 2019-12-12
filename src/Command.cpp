#include <iostream>
#include "../header/Command.h"
#include "../header/WriteFile.h"
#include "../header/WriteFileAppend.h"
#include "../header/ReadFile.h"

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
#include <queue>
#include <stdio.h>



using namespace std;

Command::Command(std::string com) {
  this->executable = com;
}

void Command::parse(std::string toParse){
  boost::regex expression {
    "#([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$"
  };
  std::string format {
    ""
  };
  //delete white space
  while (toParse[0] == ' '){
    toParse = toParse.substr(1,toParse.size());
  }


  //parse out | 
  string strippedquotes = boost::regex_replace(toParse,   boost::regex {"([^\\\\]\").*([^\\\\]\")"}, "");
  vector<string> splitPipe;
  vector<string> splitOutput;
  if(strippedquotes.find("|") != string::npos){
  boost::algorithm::split_regex(splitPipe, toParse, boost::regex("( \\| )(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
   for(string tempSplitPipe : splitPipe){
    string strippedTemp = boost::regex_replace(tempSplitPipe,   boost::regex {"([^\\\\]\").*([^\\\\]\")"}, "");
     if(strippedTemp.find(" > ") != string::npos){
      //push correct file output connector with filename 
      boost::algorithm::split_regex(splitOutput, tempSplitPipe, boost::regex("( > )(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
      PipeLine.push_back(new WriteFile(new Command(splitOutput.at(0)),splitOutput.at(1)));
     } else if(strippedTemp.find(" >> ") != string::npos){
        boost::algorithm::split_regex(splitOutput, tempSplitPipe, boost::regex("( >> )(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
        PipeLine.push_back(new WriteFileAppend(new Command(splitOutput.at(0)),splitOutput.at(1)));
     } else if (strippedTemp.find(" < ")!= string::npos){
        boost::algorithm::split_regex(splitOutput, tempSplitPipe, boost::regex("( < )(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
        PipeLine.push_back(new ReadFile(new Command(splitOutput.at(0)),splitOutput.at(1)));
     }
     else{
       //if no file output push command to list
       PipeLine.push_back(new Command(tempSplitPipe));
     }
   }
  }
  //now check for > >> <
  else{
      string strippedTemp = boost::regex_replace(toParse,   boost::regex {"([^\\\\]\").*([^\\\\]\")"}, "");
     if(strippedTemp.find(" > ") != string::npos){
      //push correct file output connector with filename 
      boost::algorithm::split_regex(splitOutput, toParse, boost::regex("( > )(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
      PipeLine.push_back(new WriteFile(new Command(splitOutput.at(0)),splitOutput.at(1)));
     } else if(strippedTemp.find(" >> ") != string::npos){
        boost::algorithm::split_regex(splitOutput, toParse, boost::regex("( >> )(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
        PipeLine.push_back(new WriteFileAppend(new Command(splitOutput.at(0)),splitOutput.at(1)));
     } else if (strippedTemp.find(" < ")!= string::npos){
        boost::algorithm::split_regex(splitOutput, toParse, boost::regex("( < )(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
        PipeLine.push_back(new ReadFile(new Command(splitOutput.at(0)),splitOutput.at(1)));
     }

  }
  //this->PipeLine now has a sequential array with all the correctly parsed objects


 int leftInput, rightOutput, lastInput, lastOutput = 0;
 int pipeIndex = 0;
 vector<int> fdslist;
 //we will only do piping logic if there are actual pipes (or ioredirection) in our command!
 if (PipeLine.size() == 1){
   //base case: only one thing (ioredirection)
   PipeLine.at(0)->execute(0,1);
   this->args[0] = NULL;
 }

  else if (PipeLine.size() > 1) {
    int numPipes = 0;
      for (int i = 0; i < PipeLine.size(); i++){
        if (dynamic_cast <Command*> (PipeLine.at(i))){
          numPipes++;
        }
      }
    bool canExecute = false;
    
    for (unsigned i = 0; i < PipeLine.size(); i++){
      if (dynamic_cast <Command*> (PipeLine.at(i))){
          if (dynamic_cast<Command*> (PipeLine.at(i))){
            numPipes--;
            //means that say it was cat test.txt | tr A-Z a-z, where "tr A-Z a-z" is PipeLine.at(i+1)
            int fds[2]; //need a fds of 2
            int fail = pipe(fds); //we pipe the array, RD -> fds[0], WR -> fds[1]. ie, input(0) output(1)
            fdslist.push_back(fds[0]);
            fdslist.push_back(fds[1]);
            if (fail == -1){
              //return of -1 means pipe failed
              perror("pipe");
              exit(1);
            }
              dynamic_cast<Command*> (PipeLine.at(i))->oFds[0] = lastInput;
              dynamic_cast<Command*> (PipeLine.at(i))->oFds[1] = lastOutput;
              dynamic_cast<Command*> (PipeLine.at(i))->cFds[0] = fds[0];
              dynamic_cast<Command*> (PipeLine.at(i))->cFds[1] = fds[1];
            //if not first, dup2 the last output stream into stdin current input 
            if(i == 0){
              dynamic_cast<Command*> (PipeLine.at(i))->hasPrevCmd = false;
              dynamic_cast<Command*> (PipeLine.at(i))->hasNextCmd = true;
              if (!PipeLine.at(i)->execute(0, fds[1])){
                perror("pipe");
              }
            } else if(i != PipeLine.size()-1){
              dynamic_cast<Command*> (PipeLine.at(i))->hasNextCmd = true;
              dynamic_cast<Command*> (PipeLine.at(i))->hasPrevCmd = true;

              if (!PipeLine.at(i)->execute(lastInput, fds[1])){
                perror("pipe");
              }
            } else{
                dynamic_cast<Command*> (PipeLine.at(i))->hasPrevCmd = true;
                dynamic_cast<Command*> (PipeLine.at(i))->hasNextCmd = false;
                if (!PipeLine.at(i)->execute(lastInput, 1)){
                perror("pipe");
              }
            }
                     
            lastOutput = fds[1];
            lastInput = fds[0];
          }  
        }
       else {
            pipeIndex = i;
       }
         if (numPipes == 0){
            cout << "finished pipes" << endl;
            canExecute = true;
          } 
        if (canExecute){
          if (dynamic_cast<WriteFile*>(PipeLine.at(pipeIndex))){
            cout << "write" << endl;
            PipeLine.at(pipeIndex)->execute(dynamic_cast<Command*>(PipeLine.at(i-1))->cFds[1], 1);
          }
          if (dynamic_cast<WriteFileAppend*>(PipeLine.at(pipeIndex))){
            cout << "write append" << endl;
            PipeLine.at(pipeIndex)->execute(dynamic_cast<Command*>(PipeLine.at(i-1))->cFds[1], 1);
          }
          if (dynamic_cast<ReadFile*>(PipeLine.at(pipeIndex))){
            cout << "start read" << endl;
            PipeLine.at(pipeIndex)->execute(dynamic_cast<Command*>(PipeLine.at(i-1))->cFds[0], 1);
            cout << "finsih" << endl;
          }
          
        }
      
    }
   
    // handles piping completely different -- we will do everything in our Command::parse() function,
    // and not do anything in execute! so we will set args[0] = NULL (for segfault handling)
    this->args[0] = NULL;
    return;
  }
    

  //no input redirection/output redirection.
  else if (PipeLine.size() == 0){
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
      }

      //remove space??
      int num_spaces = 0;
      for (unsigned i = 0; i < arguments.size(); i++) {
        if (string(arguments.at(i)) == "\0"){
            num_spaces++;
          }
          else if (arguments.at(i)[0] != '\0'){ //remove spaces
            this->args[i] = arguments.at(i);
          }

      }
      this->args[arguments.size()-num_spaces] = NULL;
   }
}
//(fdInput, fdOutput)
bool Command::execute(int fdInput, int fdOutput) {
  parse(this->executable);
  if (args[0]==NULL){
    //no arg
    return true;
  }
  if ( string(args[0]) == "exit" || string(args[0]) == "\0") {
    exit(1);
  }
  if (string(args[0]) == "test" || string(args[0]) == "["){
    return this->Test();
  }
  //convert input into char*[] for execvp(args[0],args)
  pid_t pid = fork(); //child process. fork returns pid_t of process
  int status; //to see when status changes      
  if (pid == -1) { //error with fork
    perror("fork");
    exit(1);
  }
  bool hn = this->hasNextCmd;
  bool hp = this->hasPrevCmd;

  // Child process, calls execvp()
  if (pid == 0) {
    //basically the same as dup(), but we are using the fd from our fdInput. (less need for extra steps like closing)

    if(hn == 1 || hp == 1){
    if(hp){
      if (dup2(fdInput,0) == -1) {
        //if the return value is -1 then this means there was an error!
        perror("dup");
        exit(1);
      } 
      close(fdInput);
      close(oFds[1]);
    }
    if(hn){
      close(this->cFds[0]);
      if (dup2(fdOutput,1) == -1){
        perror("dup");
        exit(1);
      }
      close(fdOutput);
    }
    } else{
      if (dup2(fdOutput,1) == -1){
        perror("dup");
        exit(1);
      }
      if (dup2(fdInput,0) == -1) {
        //if the return value is -1 then this means there was an error!
        perror("dup");
        exit(1);
      } 
    }




    //args[0] is the command
    if (execvp(args[0], args) == -1) {
      //if returns, then this means somehting failed, maybe not a real command
      perror("execvp");
      exit(1);
      //return false;
    }
  }

  if (pid > 0) { //parent

    if(this->hasPrevCmd){
      close(this->oFds[0]);
      close(this->oFds[1]);
    }
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
