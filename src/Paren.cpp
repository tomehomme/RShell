#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include "../header/RBase.h"
#include "../header/Paren.h"

void Paren::parse(string s){}
//make paren have the same parser as executer
Paren::Paren(){
    this->right = nullptr;
    this->left = nullptr;
}
bool Paren::execute(){
    //same executer as executer
	//cout << "PAREN EXECUTE \n";
   
   return left->execute();
    
    
}

void Paren::print(){
  cout << "(";
  this->left->print();
  cout << ")";

}