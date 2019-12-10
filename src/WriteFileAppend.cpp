#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

#include "../header/WriteFileAppend.h"

WriteFileAppend::WriteFileAppend(RBase* left, string right):Connector(left,0){
    this->filename = right;
    
}



WriteFileAppend::WriteFileAppend(){

}

void WriteFileAppend::parse(string s){}

bool WriteFileAppend::execute(int fdInput, int fdOutput){

}

void WriteFileAppend::print(){

}
