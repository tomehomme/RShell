#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "gtest/gtest.h"
//#include "../src/Command.cpp"
//#include "../src/And.cpp"


TEST(AndTest, Constructor){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new And(left, right);
}

TEST(AndTest, Execute){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new And(left, right);
    test->execute();
}

TEST(AndTest, True){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new And(left, right);
    EXPECT_EQ(test->execute(), true);  
}

#endif
