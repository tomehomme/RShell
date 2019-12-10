#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <array>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

#include "../header/PipeLine.h"
#include "../header/Command.h"

using namespace std;

void PipeLine::parse(std::string toParse){
  
  string strippedquotes = boost::regex_replace(toParse,   boost::regex {"([^\\\\]\").*([^\\\\]\")"}, "");
  if(strippedquotes.find("|") == string::npos){
    pipeList.push_back(new Command(toParse));
  }
}

PipeLine::PipeLine(string toParse){
  this->executable = toParse;
  this->parse(toParse);

}

bool PipeLine::execute() {
  if(pipeList.size() == 1 ) return dynamic_cast<Command*>(pipeList.at(0))->execute();
}

void PipeLine::print(){
  cout << this->executable;

}

bool PipeLine::Test(){
    if(pipeList.size() == 1 ) return dynamic_cast<Command*>(pipeList.at(0))->Test();
}
