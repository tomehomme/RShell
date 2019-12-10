#ifndef __WRITEFILEAPPEND_H__
#define __WRITEFILEAPPEND_H__


#include "Connector.h"

class WriteFileAppend : public Connector{
  public:
    string filename;
    int fdInput = 0;
    int fdOutput = 1;
    WriteFileAppend(RBase* left, string right);
    WriteFileAppend();

    virtual bool execute(int fdInput = 0, int fdOutput = 1);
    virtual void parse(string); 
    virtual void print();
};




#endif

