#ifndef __WRITE_TEST_HPP__
#define __WRITE_TEST_HPP__

#include "gtest/gtest.h"



TEST(WriteTest, Constructor){
    RBase* test = new WriteFile(new Command("cat"), "output.txt");
}

TEST(WriteTest, Execute){
    RBase* test =  new WriteFile(new Command("cat"), "output.txt");
    test->execute(0,1);
}




#endif

