#ifndef __OR_H__
#define __OR_H__


#include "Connector.h"

class Or : public Connector{
  public:
    //RBase* left, RBase* right
   Or(RBase* left, RBase* right):Connector(left,right);
       virtual bool execute();
       
    };
   
#endif
