#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
using namespace std;



// returns the distance of the begin ( to the end )
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


string replacePAREN(string &s){
   
    //cout << "ORIGINAL: " << s << endl;
    while (s.find("(") != string::npos){
        s.replace(s.find("("), distanceParen(s), "PAREN");
    }
    return s;
}


//paren search prototype
int main(){
    string testCmd = "echo hello ||  (echo A && echo B) || (echo C && echo D) || echo bye";
    string testCmd2 = "(echo A && (echo C && echo D))";

    cout << testCmd << "\nBECOMES : " << endl;
    cout << replacePAREN(testCmd) << endl;
    cout << testCmd2 << "\nBECOMES: " << endl;
    cout << replacePAREN(testCmd2) << endl;
    cout << testCmd2 << endl;
    

    return 0;
}