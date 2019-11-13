#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include "../header/RBase.h"
#include "../header/Command.h"
#include "../header/Executer.h"

Executer::Executer(std::string in){
    this->parse(in);
}


//Takes in user input, splits by ';' , "&&" and "||" to get seperate commands, 
//passes result to new Command and sets the appropriate bool flag if it is to the left of a connector. 
//It then stores the new Command into commandList.
void Executer::parse(std::string toParse){
    std::vector<std::string> parsed;
    //todo: split by connectors and populate flags 
    boost::algorithm::split_regex(parsed, toParse, boost::regex(";(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
    for(std::string par : parsed){
        Command * tmp = new Command(par);
        commandList.push_back(tmp);
        std::cout << par << "\n\n";
    }
};

void Run(){

}

int main(){
    Executer * test = new Executer("git push; git pull; echo test");
    
}