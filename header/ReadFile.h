#ifndef __READFILE_H__
#define __READFILE_H__


#include "Connector.h"

class ReadFile : public Connector{
  public:
    
    ReadFile(RBase* left, RBase* right);
    ReadFile();

    virtual bool execute();
    virtual void parse(string); 
    virtual void print();
};




#endif

