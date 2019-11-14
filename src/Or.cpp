#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include "../header/RBase.h"
#include "../header/Or.h"

void Or::parse(string s){}

Or::Or(){

}
bool Or::execute(){
	cout << "OR EXECUTE \n";
    //executes second statement only if the first one fails
    if(!this->left->execute()){
        return this->right->execute();
    }
    //if first command passes, do not execute the second one.
    else{
        return true;
    }
}

void Or::print(){
  this->left->print();
  cout << " || " ;
  this->right->print();

}