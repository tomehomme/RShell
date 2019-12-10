#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

#include "../header/ReadFile.h"
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

//ie, cat < existingInputFile

ReadFile::ReadFile(RBase* left, string right):Connector(left,0){
	//will be something like this->left = "cat" this->right = "existingInputFile"

	//change stdin to the filename
	this->filename = right;

	
	
    
}



ReadFile::ReadFile(){

}


void ReadFile::parse(string s){
	//left and rights are already parsed
}

bool ReadFile::execute(int fdInput, int fdOutput){
	//fdOutput will be 1, for stdout
	//create new command to execute the cat, or whatever and the fd number.
	//open returns a file descriptor. O_RDONLY means open for reading only.
	this->fdInput = open(filename.c_str(), O_RDONLY);
	bool success = this->left->execute(this->fdInput, fdOutput);
	//fdOutput is initialized to 1 in constructor.
	return success;
	
}

void ReadFile::print(){
	std::cout << "READFILE" << endl;
	std::cout << "file name: " << filename << endl;
}
