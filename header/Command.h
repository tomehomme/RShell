#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <vector>
#include <string>
#include "RBase.h"
class Command : public RBase{
    protected:
        std::string executable;
        bool failed;
        bool followedByAND;
        bool followedByOR;
        char* args[]; 
    public:
        //splits up input by quotes and space 
        //to populate the executable name and an array of arguments.
        
        virtual void parse(std::string toParse);
        Command(std::string com);
};      
#endif 