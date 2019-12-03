#include <iostream>
#include <map>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/include/advance.hpp>
#include "../header/RBase.h"
#include "../header/Executer.h"
#include "../header/Connector.h"
#include "../header/Command.h"
#include "../header/And.h"
#include "../header/Or.h"
#include "../header/Paren.h"
#include <queue>
#include <stack>

using namespace std;

int distanceParen(string s){
    stack <char> parens;
    int distance = 0;
    int i = s.find("(");
    for (; i < s.size(); i++){
        if (s.at(i) == '('){
            parens.push(s.at(i));
        }
          else if (s.at(i) == ')'){
           parens.pop();
           if (parens.empty()){
               distance++;
               return distance;
           }
        }
        distance++;
    }
    return distance;
}

string replacePAREN(string &s, queue <string> &commands){
    while (s.find("(") != string::npos){
        if (s.substr(s.find("(")+1,distanceParen(s)-2).size() == 0){
          //push back a empty command if user inputed ()
          commands.push(" ");
        }
        else {
          commands.push(s.substr(s.find("(")+1,distanceParen(s)-2));
        }

        s.replace(s.find("("), distanceParen(s), "^$^PAREN^$^");
    }
    return s;
}

Executer::Executer(std::string in ) {
  this->parse( in );
}

Connector * getConnector(char * type) {
  if ( * type == '&') return new And();
  if ( * type == '|') return new Or();
  return nullptr;
}

void Executer::parse(std::string toParse) {
  //remove comments
  toParse = boost::regex_replace(toParse,   boost::regex {"(( #)|(^#))(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$).*$"}, "");

  if(toParse == "") return;

  queue<string> qParen;
  string strippedquotes = boost::regex_replace(toParse,   boost::regex {"([^\\\\]\").*([^\\\\]\")"}, "");
  string nospace = boost::regex_replace(toParse,   boost::regex {" "}, "");
  if(strippedquotes.find("(") != string::npos || strippedquotes.find(")") != string::npos){
    if(nospace.find(")") - nospace.find("(") != 1){
      toParse = replacePAREN(toParse, qParen);
    }
  }
  vector < vector < pair < int, int >>> connectorIndexes;
  vector < vector < RBase * >> intermListList;
  int lastpos;

  //split the command up by ;
  //stores it into splitSemi
  vector < string > splitSemi;
  boost::algorithm::split_regex(splitSemi, toParse, boost::regex(";(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)"));

  if(toParse.find("&&") == string::npos && toParse.find("||") == string::npos){

      for (int i = 0; i < splitSemi.size(); i++){
        if (boost::algorithm::trim_copy(splitSemi.at(i)) == "^$^PAREN^$^"){
          commandList.push_back(new Executer(qParen.front()));
          qParen.pop();
        } else{
          commandList.push_back(new Command(splitSemi.at(i)));
        }
      }    
      return;
  }

  //connector splitting regex
  boost::regex conex2 {"(&&(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)|\\|\\|(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$))"};


  //For every command entered (seperated by semicolon), generate a pair<int,int> of indexes for each connector using a regex iterator (regex above)
  for (int i = 0; i < splitSemi.size(); ++i) {
    vector < pair < int, int > > tempConMap;
    string par = splitSemi.at(i);

    //dummy connector so that the end gets put into the int pair list
    par += " && ";

    boost::sregex_iterator p1(par.begin(), par.end(), conex2);
    boost::sregex_iterator p2;
    if (p1 == p2) {
      break;
    }
    lastpos = -3;
    for (; p1 != p2; ++p1) {
      tempConMap.push_back(pair < int, int > (lastpos + 3, ( * p1).position()));
      lastpos = ( * p1).position();
    }
    connectorIndexes.push_back(tempConMap);
  }
  //Now connectorIndexes has a pair of ints such that substr(first, second) is our command.
  //Therefore, at(first - 3) gives us a char for our connector
  //Pass this substring into command, using our getconnector helper function to determine connector
  //We must do this for every command we are given, so we iterate thru splitsemi.
  for (int i = 0; i < splitSemi.size(); ++i) {

    vector < RBase * > intermList;
    vector < pair < int, int >> tempConMap = connectorIndexes.at(i);
    for (int j = 0; j < connectorIndexes.at(i).size(); ++j) {
      
      if (splitSemi.at(i).substr(tempConMap.at(j).first, tempConMap.at(j).second - tempConMap.at(j).first).find("^$^PAREN^$^") != string::npos ){
        //if it is PAREN, then we will push the paren command onto our intermList.
        //We do this by initializing Paren with an Executer as its left*.
        Connector * con = nullptr;
        Paren* par = new Paren(new Executer(qParen.front()), nullptr);
        if (tempConMap.at(j).first - 3 > 0) {
          con = getConnector( & splitSemi.at(i).at(tempConMap.at(j).first - 3));
          con->left = nullptr;
          con->right = nullptr;
          if (tempConMap.at(j).second != splitSemi.at(i).size() - 1) intermList.push_back(con);
        }   
        qParen.pop();
        intermList.push_back(par);
      }
      //made an else statement for if it is not a PAREN keyword
      else{
        Command * cmd = nullptr;
        Connector * con = nullptr;
        con = nullptr;
        cmd = new Command(splitSemi.at(i).substr(tempConMap.at(j).first, tempConMap.at(j).second - tempConMap.at(j).first));

        if (tempConMap.at(j).first - 3 > 0) {
          con = getConnector( & splitSemi.at(i).at(tempConMap.at(j).first - 3));
          con->left = nullptr;
          con->right = nullptr;
          if (tempConMap.at(j).second != splitSemi.at(i).size() - 1) intermList.push_back(con);
        }
        intermList.push_back(cmd);
       }
      }
      intermListList.push_back(intermList);

  }

  //Now we have a vector of vectors. Each index of the outer vector represents a seperate command (split up by ;) 
  //Each index of the inner vector represents either a Command or a Connector object. These objects are in order. 
  //Now we must generate an expression tree using these objects:
  for (vector < RBase * > intermList: intermListList) {
    if (intermList.size() == 1) {
      commandList.push_back((intermList.at(0)));
    } else {

      vector < RBase * > command;
      stack < RBase * > commandStack;

      bool foundConnector = false;
      string connectorType = "";

      for (int i = 0; i < intermList.size(); i++) {
        if (dynamic_cast < And * > (intermList.at(i)) && !foundConnector) {
          connectorType = "&&";
          foundConnector = true;
        }
        else if (dynamic_cast < Or * > (intermList.at(i)) && !foundConnector) {
          connectorType = "||";
          foundConnector = true;
        }
        else if (!foundConnector) {
          commandStack.push(intermList.at(i));
        }
        else {
          if (connectorType == "&&") {
              dynamic_cast<And*>(intermList.at(i-1))->left = commandStack.top();
              dynamic_cast<And*>(intermList.at(i-1))->right = intermList.at(i);
              commandStack.pop();
              commandStack.push(intermList.at(i-1));
          } else if (connectorType == "||") {
              dynamic_cast<Or*>(intermList.at(i-1))->left = commandStack.top();
              dynamic_cast<Or*>(intermList.at(i-1))->right = intermList.at(i);
              commandStack.pop();
              commandStack.push(intermList.at(i-1));
          }
          foundConnector = false;
          connectorType = "";
        }
      }

      //Finally, we may populate our command list
      while (!commandStack.empty()) {
        commandList.push_back(commandStack.top());
        commandStack.pop();
      }

    } 
  }
  return ;
}

bool Executer::execute( int fdInput, int fdOutput) {
  bool success = true;

  for (int i = 0; i + 1 < commandList.size(); i++) {
    this->commandList.at(i)->execute();
  }

  success = commandList.at(commandList.size()-1)->execute();
  commandList.clear();

  return success;
}

void Executer::print() {
  for (int i = 0; i < commandList.size(); i++) {
    commandList.at(i)->print();
  }
}

