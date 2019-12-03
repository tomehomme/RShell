#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__


#include "RBase.h"

class Connector : public RBase{
  public:
    RBase* left;
    RBase* right;
    Connector(){}
    Connector(RBase* left, RBase* right){this->left = left; this->right = right;}
    virtual bool execute(int fdInput, int fdOutput) = 0;
    virtual void parse(string) = 0;
    virtual void print() = 0;
    private:
};




#endif
