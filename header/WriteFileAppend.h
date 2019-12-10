#ifndef __WRITEFILEAPPEND_H__
#define __WRITEFILEAPPEND_H__


#include "Connector.h"

class WriteFileAppend : public Connector{
  public:
    string filename;
    int fdInput;
    int fdOutput;
    WriteFileAppend(RBase* left, string right);
    WriteFileAppend();

    virtual bool execute();
    virtual void parse(string); 
    virtual void print();
};




#endif

