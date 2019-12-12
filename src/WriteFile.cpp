#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
//#include "../header/RBase.h"
#include "../header/WriteFile.h"
#include <fcntl.h>

using namespace std;

WriteFile::WriteFile(RBase* left, string right):Connector(left,0){
    this->filename = right;
 }



WriteFile::WriteFile(){

}

void WriteFile::parse(string s){}

bool WriteFile::execute(int fdInput,int fdOutput){
	//means, write only, if not created then create, and if there is stuff in the file
	//then we will write over it. S_IRUSR allows user to read
	this->fdOutput = open(filename.c_str(),O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR  | S_IRGRP | S_IWGRP | S_IWUSR);

	bool success = left->execute(0,this->fdOutput);
}

void WriteFile::print(){
	cout << "WriteFile" << endl;
	cout << "file name: " << this->filename << endl;
}
