#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

#include "../header/ReadFile.h"
#include <sys/stat.h>
#include <fcntl.h>



//ie, cat < existingInputFile

ReadFile::ReadFile(RBase* left, RBase* right):Connector(left,right){
	//will be something like this->left = "cat" this->right = "existingInputFile"

	//change stdin to the filename
	string file = this->right->executable;

	//open returns a file descriptor. O_RDONLY means open for reading only.
	int fd = open(file.c_str(), O_RDONLY);
    
}



ReadFile::ReadFile(){

}


void ReadFile::parse(string s){
	//left and rights are already parsed
}

bool ReadFile::execute(int fdInput, int fdOutput){
	//fdInput is created during construction
	//fdOutput will be 1, for stdout

	//create new command to execute the cat, or whatever and the fd number.

	fdOutput = 1;
	bool success = this->left->execute(fdInput, fdOutput);

	return success;
	
}

void ReadFile::print(){
	std::cout << "READFILE" << endl;
}
