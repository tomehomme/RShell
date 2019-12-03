#ifndef __WRITEFILE_H__
#define __WRITEFILE_H__


#include "Connector.h"

class WriteFile : public Connector{
  public:
    
    WriteFile(RBase* left, RBase* right);
    WriteFile();

    virtual bool execute( int fdInput, int fdOutput);
    virtual void parse(string); 
    virtual void print();
};




#endif

