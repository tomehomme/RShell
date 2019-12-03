#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
//#include "../header/RBase.h"
#include "../header/WriteFile.h"

WriteFile::WriteFile(RBase* left, RBase* right):Connector(left,right){

    
}



WriteFile::WriteFile(){

}

void WriteFile::parse(string s){}

bool WriteFile::execute(int fdInput, int fdOutput){

}

void WriteFile::print(){

}
