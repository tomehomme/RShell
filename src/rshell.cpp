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
  // Command* ls = new Command("echo #b");
  // ls->execute();
   bool cont = true;
   while (cont){
    string inputs;
    cout << "$ ";
 
    getline(cin, inputs); 
    //change to inputs
    Executer* execute = new Executer(inputs);
    //execute->execute();
	//cout << "finished execute. " <<endl;

    execute->execute();
}
//	cout << "finished execute. " <<endl;
    return 0;

}

