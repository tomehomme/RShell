#ifndef __SEMI_H__
#define __SEMI_H__


#include "Connector.h"

class Semi : public Connector{
  public:
    
   Semi(RBase* left, RBase* right):Connector(left,right){}
       virtual bool execute();
	virtual void parse(string);       
};
  
#endif

