#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include "../header/RBase.h"

#include "../header/Executer.h"

using namespace std;

Executer::Executer(std::string in){
   cout << "parsing: " << endl;  this->parse(in);
}


//Takes in user input, splits by ';' , "&&" and "||" to get seperate commands, 
//passes result to new Command and sets the appropriate bool flag if it is to the left of a connector. 
//It then stores the new Command into commandList.
void Executer::parse(std::string toParse){
   cout << toParse << endl;
	//  std::vector<std::string> parsed;
    //todo: split by connectors and populate flags 
   // boost::algorithm::split_regex(parsed, toParse, boost::regex(";(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
  //   for(std::string par : parsed){
	// cout << "par" << endl;
  //       Command * tmp = new Command(par);
	// //push back a new command into our commandList vector
  //       commandList.push_back(tmp);
  //       std::cout << par << "\n\n";
  //   }
 //TEST:...DELETE LATER
 //AND TEST.. DELETE LATER
 RBase* ls = new Command("ls");
 RBase* echo = new Command("echo");
   RBase*  test = new Semi(ls, echo);
  commandList.push_back(test);
   commandList.push_back(new Command("\0"));
}


bool Executer:: execute(){
  bool success = true;
  for (int i = 0; i < commandList.size(); i++){
//	cout << "executing" << endl;
    this->commandList.at(i)->execute();
  }
 return success;
}

