#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <vector>
#include <string>
#include "RBase.h"

class Command : public RBase{
    public:
        std::string executable;
        char* args[MAX_ARGS]; 
        //splits up input by quotes and space 
        //to populate the executable name and an array of arguments.
        virtual bool  execute(int fdInput = 0, int fdOutput = 1); 
        virtual void parse(std::string toParse);
        Command(std::string com);
        //option: output / input override.
        // 1 : write output to filename
        // 2 : write output appended to filename
        // 3 : read input from filename
        Command(std::string par, int option, std::string filename);
        int option;
        std::string filename;
        bool Test();
        vector <RBase*> PipeLine;
        bool hasPrevCmd=0;
        bool hasNextCmd=0;
        int fileDesc=0;
        int oFds[2];
        int cFds[2];
	virtual void print();
};      
#endif // __COMMAND_H__
