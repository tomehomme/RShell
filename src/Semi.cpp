#include <iostream>
#include <boost/tokenizer.hpp>
 #include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include "../header/RBase.h"
#include "../header/Semi.h"
 
void Semi::parse(string s){}

bool Semi::execute(){
    //executes both statements
    this->left->execute();
    this->right->execute();
    //will execute everything always
    return true;
}
