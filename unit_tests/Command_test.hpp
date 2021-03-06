#ifndef __COMMAND_TEST_HPP__
#define __COMMAND_TEST_HPP__

#include "gtest/gtest.h"
//#include "../src/Command.cpp"


TEST(CommandTest, Constructor){
    RBase* test = new Command("echo hello");
    test->print();
    cout << endl;

}

TEST(CommandTest, Execute){
    RBase* test = new Command("ls");
    test->execute(0,1);
}
TEST(CommandTest, multipleArgs){
  RBase* test = new Command("ls -l -a");
    test->execute(0,1);
}


TEST(CommandTest, commentedOut){
  RBase* test = new Command("echo #a");
    test->execute(0,1);
}


TEST(CommandTest, notRealArg){
    RBase* test = new Command("NOTREAL");
    test->execute(0,1);

}



#endif
