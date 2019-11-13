#ifndef __SEMI_TEST_HPP__
#define __SEMI_TEST_HPP__

#include "gtest/gtest.h"
//#include "../src/Semi.cpp"


TEST(SemiTest, Constructor){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new Semi(left, right);
}

TEST(SemiTest, Execute){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new Semi(left, right);
    test->execute();
}

#endif
