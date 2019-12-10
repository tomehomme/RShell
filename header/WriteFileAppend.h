#ifndef __WRITEFILEAPPEND_H__
#define __WRITEFILEAPPEND_H__


#include "Connector.h"

class WriteFileAppend : public Connector{
  public:
    string filename;

    WriteFileAppend(RBase* left, string right);
    WriteFileAppend();

    virtual bool execute(int fdInput, int fdOutput);
    virtual void parse(string); 
    virtual void print();
};




#endif

