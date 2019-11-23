#ifndef __EXECUTE_TEST_HPP__
#define __EXECUTE_TEST_HPP__

#include "gtest/gtest.h"

TEST(ExecuteTest, Or){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new Or(left, right);
    test->execute();
}
TEST(ExecuteTest, And){
    RBase* left = new Command("echo and");
    RBase* right = new Command("ls -a");
    RBase* test = new And(left, right);
    test->execute();
}
TEST(ExecuteTest, Command){
    RBase* test = new Command("echo command");
    test->execute();
}
TEST(ExecuteTest, MultipleArgs){
    RBase* test = new Command("ls -a -l");
    test->execute();
}
TEST(ExecuteTest, CommentedOut){
     RBase* test = new Command("echo #b");
    test->execute();
}
TEST(ExecuteTest, CommentedOut2){
     RBase* test = new Command("#echo b");
    test->execute();
}
TEST(ExecuteTest, AndOr){
    RBase* Orleft = new Command("echo");
    RBase* Orright = new Command("ls");
    RBase* oR = new Or(Orleft, Orright);
    RBase* left = new Command ("echo left");
    RBase* test = new And(left, oR);
    test->execute();
}
TEST(ExecuteTest, OrAnd){
    RBase* andLeft = new Command("echo and");
    RBase* andRight = new Command("ls");
    RBase* and_ = new And(andLeft, andRight);
    RBase* left = new Command ("echo left");
    RBase* test = new Or(left, and_);
    test->execute();
}
TEST(ExecuteTest, AndOrAnd){
     RBase* andLeft = new Command("echo andLeft");
    RBase* andRight = new Command("echo andRight");
    RBase* and_ = new And(andLeft, andRight);
    
    RBase* Orleft = new Command("echo orLeft");
    RBase* Orright = new Command("echo orRight");
    RBase* oR = new Or(Orleft, Orright);

    RBase* AndOrAnd = new And(oR,and_);

    AndOrAnd->execute();
}


#endif


