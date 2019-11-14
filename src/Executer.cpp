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
#include <queue> 
#include <stack>

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
  
  
  //checks for a single command -- just pushes this single command without going through the connector check
  if (splitSemi.size() == 1){
	if (splitSemi.at(0).find("&&") == string::npos && splitSemi.at(0).find("||") == string::npos){
		commandList.push_back(new Command(splitSemi.at(0))); 
		return;
	}
 
 
	}
  //connector splitting regex
  boost::regex conex2{"(&&(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)|\\|\\|(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$))"};
//tome: i added i+1, used to be i 
 for(int i = 0; i < splitSemi.size(); ++i){
    vector< pair<int,int> > tempConMap;
    string par = splitSemi.at(i);
    //add dummy connector to the end
    par += " && ";
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

  vector<vector<RBase*>> intermListList;

  //use locations to generate appropriate objects
  for(int i = 0; i < splitSemi.size(); ++i){
    cout << "Indexes for " << splitSemi.at(i) << endl;
    vector<pair<int,int>> tempConMap = connectorIndexes.at(i);
    Command * cmd = nullptr;
    Connector * con = nullptr;
    vector<RBase*> intermList;

    for(int j = 0; j < tempConMap.size(); ++j){
      con = nullptr;
      cmd = new Command(splitSemi.at(i).substr(tempConMap.at(j).first, tempConMap.at(j).second - tempConMap.at(j).first));
     
//COMMENT OUT THIS LATER
     cout <<"COMMANDS: " << cmd->executable << endl; 

      if(tempConMap.at(j).first-3 > 0){
        //get connector of proper type
        con = getConnector(&splitSemi.at(i).at(tempConMap.at(j).first-3));
        con->left = nullptr;
        con->right = nullptr;
        //cout << "second: " << tempConMap.at(j).second << " size: " << splitSemi.at(i).size() << endl; 
        if(tempConMap.at(j).second != splitSemi.at(i).size() -1 ) intermList.push_back(con);
      }
      intermList.push_back(cmd);
    }
    cout << endl << endl;
    intermListList.push_back(intermList);
  }

  //each group of commands has a list of objects. 
  for(vector<RBase*> intermList : intermListList){
        cout << "COMMAND GROUP PARSED: \n";
        //going through each object:
        for(int k = 0; k < intermList.size(); ++k){
            if(dynamic_cast<Command*>(intermList.at(k))) cout << "Command Index: " << k << " Contents: " << dynamic_cast<Command*>(intermList.at(k))->executable <<endl;
            if(dynamic_cast<And*>(intermList.at(k))){
                cout << "AND     Index: " << k ;
                if(dynamic_cast<And*>(intermList.at(k))->left!= nullptr) cout <<" Left: " << (dynamic_cast<And*>(intermList.at(k))->left)->executable;
                cout << endl;

            }
            if(dynamic_cast<Or*>(intermList.at(k))){
                cout << "Or      Index: " << k ;
                if(dynamic_cast<Or*>(intermList.at(k))->left!= nullptr) cout <<" Left: " << (dynamic_cast<Or*>(intermList.at(k))->left)->executable ;
                cout << endl;

            }
        }
  

        cout << endl<< endl;

        //my attempt at sorting code, can you try something here?
        //if you put dynamic cast in an if statement you can check type.
       vector<RBase*>command; 
  
  
  //check for single command (should not actually execute, since checks for this after splitSemi)     
	if (intermList.size() == 1 ){
		cout << "ONE COMMAND: " << intermList.at(0)->executable<<endl;
		commandList.push_back(new Command(intermList.at(0)->executable));
		return;
	}
 
    //try stacks --> loop through until intermList size.
    //on stack: push command --> next push will be a connector.
    //pop off connector(keep track if it is and or or), pop off stack again for LEFT --> make new command for this
    //next loop push onto stack. pop it off and makke this into the RIGHT of the connector
    //push this RBase* connector = CONNECTORTYPE onto the stack.
    
    stack<RBase*> commandStack;
    bool foundConnector = false;
    string connectorType = "";
    cout << "SIZE OF INTERMLIST: " << intermList.size() << endl;
    for(int i = 0; i < intermList.size(); i++){
      //check if the connector is && and we have not encountered a connector yet
      if (dynamic_cast<And*>(intermList.at(i)) && !foundConnector){
        cout << "FOUND AND. INDEX: " << i << endl;
        connectorType = "&&";
        foundConnector = true;
      }
      //check if the connector is || and we have not encountered a connector yet
      else if (dynamic_cast<Or*>(intermList.at(i)) && !foundConnector){
        cout << "FOUND OR. INDEX: " << i << endl;
        connectorType = "||";
        foundConnector = true;
      }
        //if we have not found a connector and it is not OR or AND, this is the LEFT of the connector
      else if (!foundConnector){
        cout << "FOUND LEFT: "; intermList.at(i)->print(); cout << endl;
        commandStack.push(intermList.at(i));
      } 
      //found a connector and the position of the vector is not a connector, then this is the RIGHT
      else{
          if (connectorType == "&&"){
            cout << "FOUND RIGHT: "; intermList.at(i)->print(); cout << endl;
              cout << "PRINTING LEFT: "; commandStack.top()->print() ; cout << endl;
              RBase* newAnd = new And(commandStack.top(), intermList.at(i));
              //newAnd->print();
              //pop off LEFT
              commandStack.pop();
              //push this new RBase* (AND) onto the stack
              commandStack.push(newAnd);
              
          }
          else if (connectorType == "||"){
            cout << "FOUND RIGHT: "; intermList.at(i)->print(); cout << endl;
              RBase* newOr = new Or(commandStack.top(), intermList.at(i));
              //pop off LEFT
              commandStack.pop();
              //push this new RBase* (OR) onto the stack
              commandStack.push(newOr);
          }
          //reset, since we found everything.
          foundConnector = false;
          connectorType = "";
      }
    
    }
    
    //PREVIOUS TRY: USING THE VECTOR AND CHAGING POSITIONS
   /* for(int i = 1; i+1  < intermList.size(); i=i+2){
        if(dynamic_cast<And*>(intermList.at(i))){
        cout << "PUSHING AND BACK INTO COMMAND" << endl;
          RBase* newRight = new Command(intermList.at(i+1)->executable);
          intermList.at(i+1) = new And(intermList.at(i-1),newRight);
            } else if(dynamic_cast<Or*>(intermList.at(i))){
                cout << "PUSHING OR INTO COMMAND" << endl;
                RBase* right = new Command(intermList.at(i+1)->executable);
                intermList.at(i+1) = new Or(intermList.at(i-1), right);       
            }
            
    }*/
        

        //the same print stuff again to see the changes
     /*   for(int k = 0; k < intermList.size(); ++k){
            if(dynamic_cast<Command*>(intermList.at(k))) cout << "Command Index: " << k << " Contents: " << dynamic_cast<Command*>(intermList.at(k))->executable <<endl;
            if(dynamic_cast<And*>(intermList.at(k))){
                cout << "AND     Index: " << k ;
               // if(dynamic_cast<And*>(intermList.at(k))->left!= nullptr) cout <<" Left: " << (dynamic_cast<And*>(intermList.at(k))->left)->executable ;
                cout << endl;
            }
            if(dynamic_cast<Or*>(intermList.at(k))){
                cout << "Or      Index: " << k ;
             //   if(dynamic_cast<Or*>(intermList.at(k))->left!= nullptr) cout <<" Left: " << (dynamic_cast<Or*>(intermList.at(k))->left)->executable;
                cout << endl;
            }
        }
     */
    //last item is the tree
  	//command.push_back(intermList.at(intermList.size()-1));  
    
    //my stuff
    //cout << "COMMAND VECTOR SIZE:"<<command.size() << endl;
    //for (int i = 0; i < command.size(); i++){
      //commandList.push_back(command.at(command.size()-1));
    
   // }
    
    
    while(!commandStack.empty()){
        commandList.push_back(commandStack.top());
        commandStack.pop();
    }
    cout << "PRINTING COMMANDLIST" << endl;
    this->print();
    cout << endl;
    //end mystuff

}
}//
//

bool Executer:: execute(){
  bool success = true;
  for (int i = 0; i < commandList.size(); i++){
	cout << "executing" << endl;
	 this->commandList.at(i)->execute();
 }
 return success;
}

void Executer:: print(){
  for (int i = 0; i < commandList.size(); i++){
    commandList.at(i)->print();
  
  }

}
