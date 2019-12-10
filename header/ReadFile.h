#ifndef __READFILE_H__
#define __READFILE_H__


#include "Connector.h"

class ReadFile : public Connector{
  public:
    string filename;

    ReadFile(RBase* left, string right);
    ReadFile();

    virtual bool execute(int fdInput, int fdOutput);
    virtual void parse(string); 
    virtual void print();
};




#endif

