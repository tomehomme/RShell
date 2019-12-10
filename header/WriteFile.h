#ifndef __WRITEFILE_H__
#define __WRITEFILE_H__


#include "Connector.h"

class WriteFile : public Connector{
  public:
    string filename;
    int fdInput = 0;
    int fdOutput = 1;
    WriteFile(RBase* left, string right);
    WriteFile();

    virtual bool execute(int fdInput = 0, int fdOutput = 1);
    virtual void parse(string); 
    virtual void print();
};




#endif

