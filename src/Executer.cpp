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
             // cout << "found )" << endl;
           parens.pop();
           if (parens.empty()){
               distance++;
               //cout << "DISTANCE BETWEEN: " << distance << endl;
               return distance;
           }
        }
        distance++;
    }
    //cout << "DISTANCE BETWEEN: " << distance << endl;
    return distance;
}

string replacePAREN(string &s, queue <string> &commands){
    //cout << "ORIGINAL: " << s << endl;
    while (s.find("(") != string::npos){
      // cout << s.substr(s.find("(")+1, distanceParen(s)-2) << endl;
        commands.push(s.substr(s.find("(")+1,distanceParen(s)-2));
        s.replace(s.find("("), distanceParen(s), "PAREN");
    }
    return s;
}

Executer::Executer(std::string in ) {
  // cout << "parsing: " << endl;
  this->parse( in );
}

Connector * getConnector(char * type) {
  if ( * type == '&') return new And();
  if ( * type == '|') return new Or();
  return nullptr;
}

void Executer::parse(std::string toParse) {
  //stores the commands of when we replaced them.
  // (echo b) --> echo b
  queue<string> qParen;
  toParse = replacePAREN(toParse, qParen);

  vector < vector < pair < int, int >>> connectorIndexes;

  if(toParse == "") return;
  
  vector < vector < RBase * >> intermListList;

  // if there are no connectors (only semi colons)
  if(toParse.find("&&") == string::npos && toParse.find("||") == string::npos){
       // cout << "FOUND NO CONNECTORS!!" << endl;
       boost::regex expression {
    "(( #)|(^#))(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$).*$"
  };
      std::string format {
        ""
      };
      toParse = boost::regex_replace(toParse, expression, format);
      vector < string > splitSemi;
      //ADDED SEMI INTO SPLIT SEMI

      //deleted ; in boost::regex(";(?=...
      boost::algorithm::split_regex(splitSemi, toParse, boost::regex(";(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)"));
      for (int i = 0; i < splitSemi.size(); i++){
        commandList.push_back(new Command(splitSemi.at(i)));
      }
      return;
  }
  //first, lets remove comments 
  boost::regex expression {
    "(( #)|(^#))(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$).*$"
  };
  //boost::regex expression {
    //"#([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$"
  //};
  std::string format {
    ""
  };
  toParse = boost::regex_replace(toParse, expression, format);
  // cout << toParse << endl;

  //now lets seperate our string by ;
  vector < string > splitSemi;
  //ADDED SEMI INTO SPLIT SEMI

  //deleted ; in boost::regex(";(?=...
  boost::algorithm::split_regex(splitSemi, toParse, boost::regex(";(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)"));
  int lastpos;

  bool hasConnectors = true;
  //checks for a single command -- just pushes this single command without going through the connector check
  if (splitSemi.size() == 1) {
    //ADDED SEMI
    if (splitSemi.at(0).find("&&") == string::npos && splitSemi.at(0).find("||") == string::npos) {
      commandList.push_back(new Command(splitSemi.at(0)));
      return;
    }

  }
  //connector splitting regex
  boost::regex conex2 {
    "(&&(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)|\\|\\|(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$))"
  };
  //tome: i added i+1, used to be i 

  for (int i = 0; i < splitSemi.size(); ++i) {
    vector < pair < int, int > > tempConMap;
    string par = splitSemi.at(i);
    //add dummy connector to the end
    par += " && ";
    //lets note the locations and selection groups of each connector
    boost::sregex_iterator p1(par.begin(), par.end(), conex2);
    boost::sregex_iterator p2;
    // cout << "checking for connectors in string " << par << endl;
    if (p1 == p2) {
      // cout << "none \n" << endl;
      //tome: ADDED BREAK AFTER cout none
      break;
    }
    lastpos = -3;
    for (; p1 != p2; ++p1) {
      tempConMap.push_back(pair < int, int > (lastpos + 3, ( * p1).position()));
      lastpos = ( * p1).position();
    }
    connectorIndexes.push_back(tempConMap);
  }

  

  //use locations to generate appropriate objects
  for (int i = 0; i < splitSemi.size(); ++i) {
    //cout << "Indexes for " << splitSemi.at(i) << endl;

    vector < RBase * > intermList;

    for (int j = 0; j < connectorIndexes.at(i).size(); ++j) {
      vector < pair < int, int >> tempConMap = connectorIndexes.at(i);
      Command * cmd = nullptr;
      Connector * con = nullptr;
      con = nullptr;
      cmd = new Command(splitSemi.at(i).substr(tempConMap.at(j).first, tempConMap.at(j).second - tempConMap.at(j).first));
      // cout << "LINE 118: ";
     // cmd->print();
      // cout << endl;

      //COMMENT OUT THIS LATER
      // cout << "COMMANDS: " << cmd->executable << endl;

      if (tempConMap.at(j).first - 3 > 0) {
        //get connector of proper type
        con = getConnector( & splitSemi.at(i).at(tempConMap.at(j).first - 3));
        con->left = nullptr;
        con->right = nullptr;
        // cout << "second: " << tempConMap.at(j).second << " size: " << splitSemi.at(i).size() << endl;
        if (tempConMap.at(j).second != splitSemi.at(i).size() - 1) intermList.push_back(con);
      }
      // cout << "pushing command:" << cmd->executable << endl;
      //chand intermList.push_back(cmd) to  intermList.push_back(new Command(cmd->executable));
      intermList.push_back(new Command(cmd->executable));
    }
    // cout << endl << endl;
    intermListList.push_back(intermList);
  }

  //each group of commands has a list of objects. 
  for (vector < RBase * > intermList: intermListList) {
    // cout << "TOTAL INTERMLISTS TO GO THROU: " << intermListList.size() << endl;
    // cout << "COMMAND GROUP PARSED: \n";
    //going through each object:
    // cout << "INTERMLIST SIZE " << intermList.size() << endl;
    //check for single command (echo a; echo b)     
    if (intermList.size() == 1) {
      // cout << "ONE COMMAND: ";
      //intermList.at(0)->print();
      // cout << endl;
      commandList.push_back((intermList.at(0)));
      //adding break for this for loop
    } else {
      for (int k = 0; k < intermList.size(); ++k) {
       // if (dynamic_cast < Command * > (intermList.at(k))) cout << "Command Index: " << k << " Contents: " << dynamic_cast < Command * > (intermList.at(k))->executable << endl;
        if (dynamic_cast < And * > (intermList.at(k))) {
          // cout << "AND     Index: " << k;
       //   if (dynamic_cast < And * > (intermList.at(k))->left != nullptr) cout << " Left: " << (dynamic_cast < And * > (intermList.at(k))->left)->executable;
          // cout << endl;

        }
        if (dynamic_cast < Or * > (intermList.at(k))) {
          // cout << "Or      Index: " << k;
        //  if (dynamic_cast < Or * > (intermList.at(k))->left != nullptr) cout << " Left: " << (dynamic_cast < Or * > (intermList.at(k))->left)->executable;
          // cout << endl;

        }

      }

      // cout << endl << endl;
      vector < RBase * > command;

      //try stacks --> loop through until intermList size.
      //on stack: push command only if we have not found a connector yet, and the current 
      // RBase is not a connector.
      // If we have not found a connector and the current RBase is a connector, then set they connectorType to the connector (&&, ||)
      // and set foundConnector to true
      // next if we have foundConnector and the current base is not a connector, then this is the RIGHT RBase for this connector 
      //   We will set the left of the connector to the RBase we have pushed onto the top of the stack, and set the right RBase connector as the 
      //   RBase we are currently indexed on
      //   Set foundConnector to false to reset this, and set connectorType to "" reset progress for next connector(s)

      stack < RBase * > commandStack;
      bool foundConnector = false;
      string connectorType = "";
      // cout << "SIZE OF INTERMLIST: " << intermList.size() << endl;
      for (int i = 0; i < intermList.size(); i++) {
        //check if the connector is && and we have not encountered a connector yet
        if (dynamic_cast < And * > (intermList.at(i)) && !foundConnector) {
          // cout << "FOUND AND. INDEX: " << i << endl;
          connectorType = "&&";
          foundConnector = true;
        }
        //check if the connector is || and we have not encountered a connector yet
        else if (dynamic_cast < Or * > (intermList.at(i)) && !foundConnector) {
          // cout << "FOUND OR. INDEX: " << i << endl;
          connectorType = "||";
          foundConnector = true;
        }

        //if we have not found a connector and it is not OR or AND, this is the LEFT of the connector
        else if (!foundConnector) {
          // cout << "FOUND LEFT: ";
         // intermList.at(i)->print();
          // cout << endl;
          commandStack.push(intermList.at(i));
        }
        //found a connector and the position of the vector is not a connector, then this is the RIGHT
        else {
          if (connectorType == "&&") {
            // cout << "FOUND RIGHT: ";
            //intermList.at(i)->print();
            // cout << endl;
            // cout << "PRINTING LEFT: ";
           // commandStack.top()->print();
            // cout << endl;
            dynamic_cast<And*>(intermList.at(i-1))->left = commandStack.top();
           dynamic_cast<And*>(intermList.at(i-1))->right = intermList.at(i);
            //RBase * newAnd = new And(commandStack.top(), intermList.at(i));
            //newAnd->print();
            //pop off LEFT
            commandStack.pop();
            //push this new RBase* (AND) onto the stack
            //commandStack.push(newAnd);
            commandStack.push(intermList.at(i-1));

          } else if (connectorType == "||") {
            // cout << "FOUND RIGHT: ";
            //intermList.at(i)->print();
            // cout << endl;
            dynamic_cast<Or*>(intermList.at(i-1))->left = commandStack.top();
            dynamic_cast<Or*>(intermList.at(i-1))->right = intermList.at(i);
            //RBase * newOr = new Or(commandStack.top(), intermList.at(i));
            //pop off LEFT
            commandStack.pop();
            //push this new RBase* (OR) onto the stack
           // commandStack.push(newOr);
           commandStack.push(intermList.at(i-1));
          }

          foundConnector = false;
          connectorType = "";
        }

      }
      while (!commandStack.empty()) {
        commandList.push_back(commandStack.top());
        commandStack.pop();
      }
      // cout << endl;
      // cout << "PRINTING COMMANDLIST" << endl;
   //  this->print();
      // cout << endl << endl;

    } //end else for if the og vector  == 1

  }
}

bool Executer::execute() {
  bool success = true;
  // cout << "executing all commmands: " << endl << endl;
  for (int i = 0; i + 1 < commandList.size(); i++) {
    this->commandList.at(i)->execute();
  }
  //the last command to run determines the success.
  success = commandList.at(commandList.size()-1)->execute();
  commandList.clear();
  //cout << "execute success: " << success << endl;
  return success;
}

void Executer::print() {
  for (int i = 0; i < commandList.size(); i++) {
    commandList.at(i)->print();

  }

}
