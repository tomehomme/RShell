#ifndef __COMMAND_TEST_HPP__
#define __COMMAND_TEST_HPP__

#include "gtest/gtest.h"
//#include "../src/Command.cpp"


TEST(CommandTest, Constructor){
    RBase* test = new Command("echo");

}

TEST(CommandTest, Execute){
    RBase* test = new Command("ls");
    test->execute();
}

TEST(CommandTest, True){
    RBase* test = new Command("ls");
    EXPECT_EQ(test->execute(), true);  
}

#endif
