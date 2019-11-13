#ifndef __EXECUTER_H__
#define __EXECUTER_H__
#include <vector>
#include <string>
#include "RBase.h"
class Executer : public RBase{
    protected:
        std::vector<RBase *> commandList;
    public:
        Executer(std::string);
        //Takes in user input, splits by ';' , "&&" and "||" to get seperate commands, 
        //passes result to new Command and sets the appropriate bool flag if it is to the left of a connector. 
        //It then stores the new Command into commandList.
        virtual void parse(std::string toParse);
        void Run();
};
#endif 