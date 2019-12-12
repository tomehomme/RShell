#ifndef __WRITE_TEST_HPP__
#define __WRITE_TEST_HPP__

#include "gtest/gtest.h"



TEST(WriteTest, Constructor){
    Executer* test = new Executer("cat names.txt > NEWOUT");
}

TEST(WriteTest, Execute){
    RBase* test =  new Executer("cat names.txt > NEWOUT");
    test->execute(0,1);
}

TEST(WriteTest, Piped){
    RBase* test =  new Executer("cat names.txt | ls >  NEWOUT");
    test->execute(0,1);
}


TEST(WriteTest, Piped2){
    RBase* test =  new Executer("cat < names.txt | ls | head -3 >  NEWOUT");
    test->execute(0,1);
}

TEST(WriteTest, Piped3){
    RBase* test =  new Executer("cat names.txt | ls | head -3 | tail -2 >  NEWOUT");
    test->execute(0,1);
}

#endif 

