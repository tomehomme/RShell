#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include <fcntl.h>
#include "../header/WriteFileAppend.h"

using namespace std;
WriteFileAppend::WriteFileAppend(RBase* left, string right):Connector(left,0){
    this->filename = right;
    
}



WriteFileAppend::WriteFileAppend(){

}

void WriteFileAppend::parse(string s){}

bool WriteFileAppend::execute(int fdInput, int fdOutput){
	//means, write only, append, and create if not existing
	this->fdOutput = open(filename.c_str(), O_WRONLY | O_APPEND | O_CREAT);
	bool success = left->execute(0,this->fdOutput);
	return success;
}

void WriteFileAppend::print(){
	cout << "WriteFileAppend" << endl;
	cout << "file name: " << filename << endl;
}
