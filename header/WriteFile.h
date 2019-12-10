#ifndef __WRITEFILE_H__
#define __WRITEFILE_H__


#include "Connector.h"

class WriteFile : public Connector{
  public:
    string filename;
    int fdInput;
    int fdOutput;
    WriteFile(RBase* left, string right);
    WriteFile();

    virtual bool execute();
    virtual void parse(string); 
    virtual void print();
};




#endif

