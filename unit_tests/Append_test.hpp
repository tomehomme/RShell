#ifndef __APPEND_TEST_HPP__
#define __APPEND_TEST_HPP__

#include "gtest/gtest.h"



TEST(APPENDTest, Constructor){
    Executer* test = new Executer("cat namex.txt >> NEWOUT");
}

TEST(APPENDTest, Execute){
    RBase* test =  new Executer("cat names.txt >> NEWOUT");
    test->execute(0,1);
}

TEST(APPENDTest, Piped){
    RBase* test =  new Executer("cat names.txt | ls >>  NEWOUT");
    test->execute(0,1);
}


TEST(APPENDTest, Piped2){
    RBase* test =  new Executer("cat < names.txt | ls | head -3 >>  NEWOUT");
    test->execute(0,1);
}

TEST(APPENDTest, Piped3){
    RBase* test =  new Executer("cat names.txt | ls | head -3 | tail -2 >>  NEWOUT");
    test->execute(0,1);
}

#endif 

