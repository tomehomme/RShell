#ifndef __OR_TEST_HPP__
#define __OR_TEST_HPP__

#include "gtest/gtest.h"
//#include "../src/Or.cpp"


TEST(OrTest, Constructor){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new Or(left, right);
    test->print();
    cout << endl;
}

TEST(OrTest, Execute){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new Or(left, right);
    test->execute();
}

TEST(Or, Print){
  RBase* left = new Command("echo hi");
  RBase* right = new Command("echo bye");
  RBase* test = new Or(left,right);
  test->print();
    cout << endl;


}
#endif
