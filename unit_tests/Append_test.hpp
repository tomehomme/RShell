#ifndef __APPEND_TEST_HPP__
#define __APPEND_TEST_HPP__

#include "gtest/gtest.h"



TEST(AppendTest, Constructor){
    RBase* test = new WriteFileAppend( new Command("cat names.txt"), "output.txt");
    cout << endl;

}

TEST(CommandTest, Execute){
    RBase* test =  new WriteFileAppend( new Command("cat names.txt"), "output.txt");
    test->execute(0,1);
}


TEST(CommandTest, notRealArg){
    RBase* test = new WriteFileAppend( new Command("NOTEREAL"), "output.txt") 
    test>execute(0,1);

}



#endif

