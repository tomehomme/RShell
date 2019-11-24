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


bool balancedParenthesis(string s){
    // using GeeksForGeeks as reference
    stack <char> parens;
    for (int i = 0; i < s.size(); i++){
        // cout << s.at(i) << endl;
        if (s.at(i) == '('){
          // cout << "   found paren ( " << endl;
            parens.push(s.at(i));
        }
          else if (s.at(i) == ')'){
            // cout << "   found paren ) " <<endl;
            if (parens.empty()){
             // cout << "   paren stack is empty! " << endl;
              // if we find a (, but we have no ) in stack, then it is unbalanced
              return false;
            }
            parens.pop();
        }
    }

    // if there is still a ( in parens, then unbalanced
    return parens.empty();
}


int main(){
    bool cont = true;
    while (cont){
        string inputs;
        cout << "$ ";
        getline(cin, inputs); 
        if(inputs != ""){
                if(balancedParenthesis(inputs)){
                    Executer* execute = new Executer(inputs);
                    execute->execute();
                } else {
                    cout << "Unbalanced parenthesis" << endl;
                
            }
            
        }
    }
    return 0;
}