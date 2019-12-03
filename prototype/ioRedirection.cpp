#include <iostream>
#include <map>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <bits/stdc++.h> 
#include <fstream>

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



using namespace std;

void readFile(string input){
    cout << "READ FILE" << endl;
    
	// Vector of string to save tokens 
	vector <string> tokens; 
	// stringstream class check1 
	stringstream check1(input); 
	string intermediate; 
	// Tokenizing w.r.t. space ' ' 
	while(getline(check1, intermediate, ' ')) 
	{ 
		tokens.push_back(intermediate); 
	} 
	const char* fileName = tokens.at(2).c_str();
    /*
	// Printing the token vector 
	for(int i = 0; i < tokens.size(); i++) 
		cout << tokens[i] << '\n'; 
    */
   //stdin from terminal
   int savestdin = dup(1);
   close(1);
   cout << "stdin saved in: " << savestdin << endl;

   int fd = open(fileName ,O_WRONLY);
   dup(fd);
   if (fd < 0){
       perror("fd");
   } else {
       cout << "fd " << fd << endl;
   }
   close(1);
   //restore stdin
    dup2(savestdin, 1);
}

void writeFile(string input){
    cout << "WRITE FILE" << endl;

}

void writeFileAppend(string input){
    cout << "WRITE FILE APPEND" << endl;
}


int main(){
    cout << "IOREDIRECTION PROTOTYPE " << endl;
    string input = "";

    while (input!="exit"){
        cout << "$ ";
        getline(cin,input);
        if (input.find("<") != string::npos){
            readFile(input);
        }
        else if (input.find(">") != string::npos){
            if (input[input.find(">") + 1] != '>'){
                writeFile(input);
            }
            else {
                writeFileAppend(input);
            }
        }
        cout << endl;
    }

    return 0;
}