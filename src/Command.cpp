#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include "../header/RBase.h"
#include "../header/Command.h"

void Command::parse(std::string toParse){

}

Command::Command(std::string com){
    this->parse(com);
}