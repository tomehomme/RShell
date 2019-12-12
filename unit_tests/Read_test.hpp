#ifndef __READ_TEST_HPP__
#define __READ_TEST_HPP__

#include "gtest/gtest.h"



TEST(ReadTest, Constructor){
    Executer* test = new Executer("cat < names.txt");
}

TEST(ReadTest, Execute){
    RBase* test =  new Executer("cat < names.txt");
    test->execute(0,1);
}

TEST(ReadTest, Piped){
    RBase* test =  new Executer("cat < names.txt | ls");
    test->execute(0,1);
}


TEST(ReadTest, Piped2){
    RBase* test =  new Executer("cat < names.txt | ls | head -3");
    test->execute(0,1);
}

TEST(ReadTest, Piped3){
    RBase* test =  new Executer("cat < names.txt | ls | head -3 | tail -2");
    test->execute(0,1);
}

#endif