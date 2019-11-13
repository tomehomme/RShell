#include <iostream>
#include <map>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/include/advance.hpp>
#include "../header/RBase.h"

#include "../header/Executer.h"
#include "../header/Connector.h"
#include "../header/Command.h"
#include "../header/And.h"
#include "../header/Or.h"

using namespace std;

vector<vector<pair<int,int>>> connectorIndexes;

Executer::Executer(std::string in){
   cout << "parsing: " << endl;  this->parse(in);
}

Connector * getConnector(char * type){
    if(*type=='&') return new And();
    if(*type=='|') return new Or();
    return nullptr;
}

Connector::Connector(){};

void Executer::parse(std::string toParse){
  //first, lets remove comments 
  boost::regex expression{"#([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$"};
  std::string format{""};
  toParse = boost::regex_replace(toParse, expression, format);
  cout << toParse << endl;
  
  //now lets seperate our string by ;
  vector<string> splitSemi;
  boost::algorithm::split_regex(splitSemi, toParse, boost::regex(";(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)") ) ;
  int lastpos;

  //connector splitting regex
  boost::regex conex2{"((?<!\\\\)\"|&&(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)|\\|\\|(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$))"};
  for(int i = 0; i < splitSemi.size(); ++i){
    vector< pair<int,int> > tempConMap;
    string par = splitSemi.at(i);
    //lets note the locations and selection groups of each connector
    boost::sregex_iterator p1(par.begin(), par.end(), conex2);
    boost::sregex_iterator p2;
    cout << "checking for connectors in string " << par << endl;
    if(p1 == p2){
      cout << "none \n" << endl;
    }
    lastpos = -3;
    for(; p1 != p2; ++p1 ) {
      tempConMap.push_back(pair<int,int>(lastpos+3,(*p1).position()));
      lastpos=(*p1).position();
    }
    connectorIndexes.push_back(tempConMap);
  }
    Command * cmd;
    Connector * con;

    vector<RBase*> intermList;

  //use locations to generate appropriate objects
  for(int i = 0; i < splitSemi.size(); ++i){
    cout << "Indexes for " << splitSemi.at(i) << endl;
    vector<pair<int,int>> tempConMap = connectorIndexes.at(i);

    for(int j = 0; j < tempConMap.size(); ++j){
      cmd = new Command(splitSemi.at(i).substr(tempConMap.at(j).first, tempConMap.at(j).second - tempConMap.at(j).first));
      
      if(tempConMap.at(j).first-3 > 0){
        //get connector of proper type
        con = getConnector(&splitSemi.at(i).at(tempConMap.at(j).first-3));
        con->left = nullptr;
        con->right = nullptr;
      }
      intermList.push_back(cmd);
      if(con) intermList.push_back(con);
    }
  

    cout << endl;
  }
  //AND TEST.. DELETE LATER
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

