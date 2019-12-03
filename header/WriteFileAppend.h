#ifndef __WRITEFILEAPPEND_H__
#define __WRITEFILEAPPEND_H__


#include "Connector.h"

class WriteFileAppend : public Connector{
  public:
    
    WriteFileAppend(RBase* left, RBase* right);
    WriteFileAppend();

    virtual bool execute(int fdInput, int fdOutput);
    virtual void parse(string); 
    virtual void print();
};




#endif

