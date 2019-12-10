#ifndef __READFILE_H__
#define __READFILE_H__


#include "Connector.h"

class ReadFile : public Connector{
  public:
    string filename;
    int fdInput = 0;
    int fdOutput = 1;

    ReadFile(RBase* left, string right);
    ReadFile();

    virtual bool execute(int fdInput = 0, int fdOutput = 1);
    virtual void parse(string); 
    virtual void print();
};




#endif

