#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
//#include "../header/RBase.h"
//#include "../header/Command.h"
#include "../header/Executer.h"

using namespace std;
Executer::Executer(std::string in){
   cout << "parsing: " << endl;  this->parse(in);
}


//Takes in user input, splits by ';' , "&&" and "||" to get seperate commands, 
//passes result to new Command and sets the appropriate bool flag if it is to the left of a connector. 
//It then stores the new Command into commandList.
void Executer::parse(std::string toParse){
   cout << toParse << endl;
	 std::vector<std::string> parsed;
    //todo: split by connectors and populate flags 
   // boost::algorithm::split_regex(parsed, toParse, boost::regex(";(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
    for(std::string par : parsed){
	cout << "par" << endl;
        Command * tmp = new Command(par);
	//push back a new command into our commandList vector
        commandList.push_back(tmp);
        std::cout << par << "\n\n";
    }
 //TEST:...DELETE LATER
   Command* test = new Command("ls");
   commandList.push_back(test);
  commandList.push_back(new Command("\0"));
	cout << commandList.at(0)->executable<<endl;
	cout << "finished parsing" << endl;
}


void Executer:: Run(){
 cout << "BEGGINING RUN FUNCITON" << endl; 
 pid_t pid;
  int status;
  bool previous_Success = true;
	for (int i = 0; i < this->commandList.size(); i++){
	cout << "executing: " <<  this->commandList.at(i)->executable << endl;
		if (commandList.at(i)->executable == "\0"){
			cout << "found exit.. exiting" << endl;
			exit(0);	
		} else {
    pid = fork();	 	
    if (pid == -1){
      perror("fork error child");
      exit(1);
    }
    if (pid == 0){
      execvp(commandList.at(i)->args[0], argv);
      perror("execvp");
      previous_Success = false;
    } else { //parent process
        // waitpid suspends execution of calling process until a child(pid) has changed state(status)
        pid_t w = waitpid(pid,&status, 0);
        //wait for any child process to finish first before resuming parent process
        if (w < 0){
          printf("wait");
        }
        cout << "Parent process finished" << endl;
      }
    }

	/*	else if (commandList.at(i)->followedByAND){
			pid = fork();	 	
      if (pid == -1){
        perror("fork error child");
        exit(1);
      }
      if (pid == 0){
        execvp(commandList.at(i)->args[0], commandList.at(i)->args);
        perror("execvp");
        previous_Success = false;
      } else { //parent process
          // waitpid suspends execution of calling process until a child(pid) has changed state(status)
          pid_t w = waitpid(pid,&status, 0);
          //wait for any child process to finish first before resuming parent process
          if (w < 0){
            printf("wait");
          }
          cout << "Parent process finished" << endl;
        }
    }
    else if (commandList.at(i)->followedByOR){
      pid = fork();	 	
      if (pid == -1){
        perror("fork error child");
        exit(1);
      }
      if (pid == 0){
        execvp(commandList.at(i)->args[0], commandList.at(i)->args);
        perror("execvp");
        previous_Success = false;
      } else { //parent process
          // waitpid suspends execution of calling process until a child(pid) has changed state(status)
          pid_t w = waitpid(pid,&status, 0);
          //wait for any child process to finish first before resuming parent process
          if (w < 0){
            printf("wait");
          }
          cout << "Parent process finished" << endl;
	//skip next command because it succeeded.
         if (previous_Success){
		 i++;
	}
        }
    }
 //now will execute ;
 else {
	pid = fork();
	if (pid == -1){
		perror("fork error. child");
		previous_Success = false;
		exit(1);
	}
	if (pid == 0){
		execvp(commandList.at(i)->args[0], commandList.at(i)->args);
		perror("execvp");
		previous_Success = false;
	}else {
		pid_t w = waitpid(pid, &status, 0);
		if (status > 0){
			perror("parent execvp failed");
			previous_Success = false;
		}
		if (w<0){
			cout << "wait..." << endl;
		}
		cout << "Parent process finished.." << endl;
		previous_Success = true;

	}
	
	
*/	}
}

