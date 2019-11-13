#ifndef __AND_H__
#define __AND_H__


#include "Connector.h"

class And : public Connector{
  public:
    //RBase* left, RBase* right
    And(RBase* left, RBase* right):Connector(left,right);
    virtual bool execute();
    
};




#endif
