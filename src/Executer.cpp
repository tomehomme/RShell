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

  //connector splitting regex
  boost::regex conex2{"(&&(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$)|\\|\\|(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$))"};
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
        if(intermList.size() > 1){
	if (intermList.size() == 1){
		cout << "ONE COMMAND: " << intermList.at(0)->executable << endl;
//		commandList.push_back(new Command(intermList.at(0)->executable));
}
          for(int i = 1; i+1  < intermList.size(); i=i+2){
              if(dynamic_cast<And*>(intermList.at(i))){

//MY STUFF
	cout << "intermList.at(i)-1: " << intermList.at(i)->executable << endl;
//	RBase* left = new Command(intermList.at(i-1)->executable);
//	cout << "AND LEFT: " <<left->executable << endl;
//	 RBase* right = new Command(intermList.at(i+1)->executable); 
//	cout << "AND RIGHT: " <<right->executable << endl;
	cout << "PUSHING BACK INTO COMMAND" << endl;
	RBase* newRight = new Command(intermList.at(i+1)->executable);
//	command.push_back(new And(intermList.at(i-1),intermList.at(i+1)));
	intermList.at(i+1) = new And(intermList.at(i-1),newRight);
	//commands.push_back(new And(intermList.at(k-1),intermList.at(k+1)));
//	intermList.at(k) = new And(intermList.at(k-1),intermList.at(k+1));
//END MYSEUF
              //  dynamic_cast<And*>(intermList.at(k))->left = intermList.at(k-1);
		//	cout << "INTERM LEFT:" <<intermList.at(k)->left->executable << endl;
        //        dynamic_cast<And*>(intermList.at(k))->right = intermList.at(k+1);
		//	cout << "INTERM RIGHT: " <<intermList.at(k)->right->executable << endl;
                //intermList.erase (intermList.begin(),intermList.begin()+2);
              } else if(dynamic_cast<Or*>(intermList.at(i))){
             //   dynamic_cast<Or*>(intermList.at(k))->left = intermList.at(k-1);
               // dynamic_cast<Or*>(intermList.at(k))->right = intermList.at(k+1);
               //MY STUFF
	cout << "PUSHING OR INTO COMMAND" << endl;
	RBase* right = new Command(intermList.at(i+1)->executable);
//	command.push_back(new Or(intermList.at(i-1),intermList.at(i+1)));
	intermList.at(i+1) = new Or(intermList.at(i-1), right);          
    // RBase* left = new Command(intermList.at(i-1)->executable); RBase* right = new Command(intermList.at(i+1)->executable); 
	//	command.push_back(new Or(left,right));
	//	intermList.at(i+1) = new Or(left,right);
           //    commands.push_back(new Or(intermList.at(k-1),intermList.at(k+1)));
             //  intermList.at(k) = new Or(intermList.at(k-1),intermList.at(k+1));
               //END MYSUTFF
               //
              //  intermList.erase (intermList.begin(),intermList.begin()+2);
              }
              
          }
        }

        //the same print stuff again to see the changes
        for(int k = 0; k < intermList.size(); ++k){
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
  	command.push_back(intermList.at(intermList.size()-1));  
    
    //my stuff
    cout << "COMMAND VECTOR SIZE:"<<command.size() << endl;
    for (int i = 0; i < command.size(); i++){
      commandList.push_back(command.at(command.size()-1));
    
    }
    }
    //end mystuff
    
  //   for(int k = 0; k < intermListList.size(); ++k){
  //     for(int j = 0; j < intermListList.at(j).size(); ++j){
  //       for(int k = 0; k < intermList.size(); ++k){
  //       if(dynamic_cast<Command*>(intermList.at(k))) cout << "Command Index: " << k << " Contents: " << dynamic_cast<Command*>(intermList.at(k))->executable <<endl;
  //       if(dynamic_cast<And*>(intermList.at(k))) cout << "AND     Index: " << k << " Left: " << &dynamic_cast<And*>(intermList.at(k))->left <<endl;
  //       if(dynamic_cast<Or*>(intermList.at(k))) cout << "OR      Index: " << k << " Left: " << dynamic_cast<Or*>(intermList.at(k))->executable <<endl;
  //       }
  //     }
  //  }




  // //populate queue
  // queue <RBase*> que; 
  
  // //temp vars
  // RBase* tm1;
  // RBase* last;

  // //we have all the objects we need, in order, in intermList. now just connect em up.

  // for(RBase* tm : intermList){
  //   while (!que.empty()){ 
  //     tm1 = que.front();
  //     que.pop();
  //     if(dynamic_cast<And*>(tm1) && last){
  //       dynamic_cast<And*>(tm1)->left = last;  

  //     }else if(dynamic_cast<Or*>(tm1) && last){
  //       dynamic_cast<Or*>(tm1)->left = last;  
  //     }

  //     last = tm1;
  //     que.pop();
  //   }
  // }
}

bool Executer:: execute(){
  bool success = true;
  for (int i = 0; i < commandList.size(); i++){
	cout << "executing" << endl;
	 this->commandList.at(i)->execute();
 }
 return success;
}

