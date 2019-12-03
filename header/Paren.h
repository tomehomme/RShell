#ifndef __PAREN_H__
#define __PAREN_H__


#include "Connector.h"

class Paren : public Connector{
  public:
    //RBase* left, RBase* right
      Paren(RBase* left, RBase* right):Connector(left,nullptr){}
      Paren();
      
      virtual bool execute( int fdInput, int fdOutput);
      virtual void parse(string); 
      virtual void print();
};
   
#endif
