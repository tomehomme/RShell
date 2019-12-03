#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

#include "../header/ReadFile.h"


//ie, cat < existingInputFile

ReadFile::ReadFile(RBase* left, string right):Connector(left,right){

    
}



ReadFile::ReadFile(){

}


void ReadFile::parse(string s){
	//left and rights are already parsed
}

bool ReadFile::execute(){
	//will be something like this->left = "cat" this->right = "existingInputFile"
	string file = this->right->executable;
	int fd = open(file.c_str(), O_WRONLY);

	
	//since the arguments are split up between our RBase* left,right we will put them together.
	this->args[0] = this->left->args[0];
	this->args[1] = this->right->args[0];
	this->args[2] = NULL;
	
	//same as Command.cpp
	if (this->args[0]==NULL){
	//no arg
	return true;
	}
	pid_t pid = fork(); //child process. fork returns pid_t of process
	int status; //to see when status changes      

	if (pid == -1) { //error with fork
		perror("fork");
		exit(1);
	}

	// Child process, calls execvp()
	if (pid == 0) {
		//args[0] is the command
		if (execvp(this->args[0], this>args) == -1) {
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

void ReadFile::print(){
	std::cout << "READFILE" << endl;
}
