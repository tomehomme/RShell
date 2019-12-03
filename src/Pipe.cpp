#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

#include "../header/Pipe.h"

Pipe::Pipe(RBase* left, RBase* right):Connector(left,right){

    
}



Pipe::Pipe(){

}

void Pipe::parse(string s){}

bool Pipe::execute(int fdInput, int fdOutput){

}

void Pipe::print(){

}
