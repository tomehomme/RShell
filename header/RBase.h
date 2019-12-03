#ifndef __RBASE_H__
#define __RBASE_H__

#include <iostream>
#include <string>

const int MAX_ARGS = 500;
using namespace std;
class RBase{
    public:
        virtual void parse(std::string ) = 0;
      	std::string executable;
      	virtual	bool execute(int fdInput, int fdOutput) = 0;
      	char* args[MAX_ARGS];
       //for testing, add a print which print out what the commands are.
       virtual void print() = 0;
};

#endif // __RBASE_H__
