#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <vector>
#include <string>
#include "RBase.h"

class Command : public RBase{
    protected:
        std::string executable;
        char* args[MAX_ARGS]; 
    public:
        //splits up input by quotes and space 
        //to populate the executable name and an array of arguments.

        virtual bool  execute(); 
        virtual void parse(std::string toParse);
        Command(std::string com);
};      
#endif // __COMMAND_H__
