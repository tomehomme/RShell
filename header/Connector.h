#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__


#include "RBase.h"

class Connector : public RBase{
  public:
    RBase* left;
    RBase* right;
    Connector(){}
    Connector(RBase* left, RBase* right){this->left = left; this->right = right;}
    virtual bool execute() = 0;
    virtual void parse(string) = 0;
    private:
};




#endif
