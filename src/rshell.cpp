#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
 #include <sys/wait.h>
#include <vector>
#include <string>
#include <sstream>
#include "Command.cpp"

#include "And.cpp"
#include "Or.cpp"
#include "Executer.cpp"

int main(){
    string inputs;
    cout << "$ ";
  // cout << "creating executer:" << endl;
  // I WILL UPDATE WHEN PARSING FUNCITON COMPLETE
    Executer* execute = new Executer("ls -la || mkdir test && echo hello || echo goodbye");
 //  cout << "finished creating executer" << endl;
//	cout << "begining executer execute()" << endl;
    //execute->execute();
	//cout << "finished execute. " <<endl;
    return 0;
}

