#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include "../header/RBase.h"
#include "../header/Paren.h"

Paren::Paren(){
    this->right = nullptr;
    this->left = nullptr;
}


void Paren::parse(string s){
  //does nothing because left (the Executer) does everything automatically
}


bool Paren::execute(){
  //will call left (the Executer's) execute
   return this->left->execute();
}

void Paren::print(){
  cout << "(";
  this->left->print();
  cout << ")";

}
