#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
//#include "../header/RBase.h"
#include "../header/And.h"

And::And(RBase* left, RBase* right):Connector(left,right){

    
}



And::And(){

}

void And::parse(string s){}

bool And::execute(){
  //  cout << "We are in AND" << endl;
    //executes second statement only if the first one passes
   if(!this->left->execute()){
        return false;
    }
    //if first command passes, then execute second one -- return if the second one passes.
    else{
        return this->right->execute();
    }
}

void And::print(){
  this->left->print();
  cout << " && ";
  this->right->print();

}
