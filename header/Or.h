#ifndef __OR_H__
#define __OR_H__


#include "Connector.h"

class Or : public Connector{
  public:
    //RBase* left, RBase* right
      Or(RBase* left, RBase* right):Connector(left,right){}
      Or();
      
      virtual bool execute(int fdInput = 0, int fdOutput = 1);
      virtual void parse(string); 
      virtual void print();
};
   
#endif
