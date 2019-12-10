#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
 #include <sys/wait.h>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include "Command.cpp"

#include "And.cpp"
#include "Or.cpp"
#include "Paren.cpp"
#include "Executer.cpp"
#include "Pipe.cpp"
#include "ReadFile.cpp"
#include "WriteFile.cpp"
#include "WriteFileAppend.cpp"

bool balancedParenthesis(string s){
   int count = 0;
   for (int i = 0; i < s.size(); i++){
     if (s.at(i) == '('){   
       count++;
     }
     else if (s.at(i) == ')'){
       count--;
       if (count < 0){
         //if it is negative, this means it is automatically false
         return false;
       }
     }
   }
   return count == 0;
}


int main(){
    bool cont = true;
    while (cont){
        string inputs;
        cout << "$ ";
        getline(cin, inputs); 
        
        inputs = boost::regex_replace(inputs,   boost::regex {"(( #)|(^#))(?=([^\"\\\\]*(\\\\.|\"([^\"\\\\]*\\\\.)*[^\"\\\\]*\"))*[^\"]*$).*$"}, "");
        inputs = boost::trim_copy(inputs);

        if(boost::regex_replace(inputs,   boost::regex {"([^\\\\]\").*([^\\\\]\")"}, "") != ""){
                if(balancedParenthesis(boost::regex_replace(inputs,   boost::regex {"([^\\\\]\").*([^\\\\]\")"}, ""))){
                    Executer* execute = new Executer(inputs);
                    execute->execute(0,1);
                } else {
                    cout << "Unbalanced parenthesis" << endl;
            }
        }
    }
    return 0;
}
