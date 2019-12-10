#ifndef __PIPELINE_H__
#define __PIPELINE_H__
#include <vector>
#include <string>
#include "RBase.h"

class PipeLine : public RBase{
    public:
        std::string executable;
        virtual bool execute(); 
        virtual void parse(std::string toParse);
        PipeLine(std::string com);
        bool Test();
	    virtual void print();
        vector<RBase*> pipeList;
};      
#endif // __Pipeline_H__
