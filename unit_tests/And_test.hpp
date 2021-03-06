#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "gtest/gtest.h"
//#include "../src/Command.cpp"
//#include "../src/And.cpp"


TEST(AndTest, Constructor){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new And(left, right);
    test->print();
    cout << endl;
}

TEST(AndTest, Execute){
    RBase* left = new Command("echo hello");
    RBase* right = new Command("ls");
    RBase* test = new And(left, right);
    test->execute(0,1);
}

TEST(AndTest, FailFirstArg){
    RBase* left = new Command("FAILTHIS");
    RBase* right = new Command("ls");
    RBase* test = new And(left,right);
    test->execute(0,1);
}

#endif
