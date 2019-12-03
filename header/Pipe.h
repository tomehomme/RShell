#ifndef __PIPE_H__
#define __PIPE_H__


#include "Connector.h"

class Pipe : public Connector{
  public:
    
    Pipe(RBase* left, RBase* right);
    Pipe();

    virtual bool execute();
    virtual void parse(string); 
    virtual void print();
};




#endif

