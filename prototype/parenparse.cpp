#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//paren search prototype
int main(){
    string testCmd = "echo hello ||  (echo A && echo B) || (echo C && echo D) || echo bye";
    string testCmd2 = "(echo A && (echo C && echo D))";

    char * searchPointer = &testCmd.at(testCmd.find('('));
    int parenCounter = 0;
    while(searchPointer < &testCmd.at(testCmd.size()-1)){
        if(*searchPointer == '(') parenCounter++;
        if(*searchPointer == ')') parenCounter--;
        searchPointer++;
        if(parenCounter == 0) break;
    }
    cout << "Distance of closing from open : " << (searchPointer - &testCmd.at(testCmd.find('(')));

    return 0;
}
