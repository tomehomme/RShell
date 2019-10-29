#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


//prototype for a looping shell function that parses data
int main(){
    stringstream buffer;
    string executable;
    char currentInput[1024];
    currentInput[0] = ' ';
    bool loop = 1;
    vector<string> args;
    string temp;

    cout << "RShell v0.0.1 alpha. \n Type 'exit' to quit. \n \n";
    while(loop){
        cout << "\033[1;32m$ > \033[0m";

        args.clear();
        buffer.clear();

        cin.getline(currentInput, 1024);
        
        //give input to stream buffer
        buffer.str(currentInput);

        if(buffer.str() == "exit"){
            cout << "Goodbye." << endl;
            loop = 0;
            return 0;
        }

        cout << "Parse Results:" << endl;

        //======= parsing code begins here =====
        //take first word 
        buffer >> executable;
        
        //store arguments
        while(buffer >> temp){
            args.push_back(temp);
        }

        cout << "Executable sent: " << executable << endl;

        cout << "Arguments sent: ";

        for(string arg : args){
            cout << arg << " ";
        }

        cout << endl << endl;
    }


    return 0;
}

