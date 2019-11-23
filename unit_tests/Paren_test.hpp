#ifndef __PAREN_TEST_HPP__
#define __PAREN_TEST_HPP__

#include "gtest/gtest.h"
//#include "../src/Executer.cpp"

TEST(ParenTest, Constructor){
    RBase* test = new Paren(new Executer("echo a"), nullptr);
    test->print();
    cout << endl;

}

TEST(ParenTest, Execute){
    RBase* test = new Paren(new Command("ls"), nullptr);
    test->execute();
}
TEST(ParenTest, multipleArgs){
  RBase* test = new Paren(new Command("ls -l -a"), nullptr);
    test->execute();
}


TEST(ParenTest, commentedOut){
  RBase* test = new Paren(new Executer("echo #a"), nullptr);
    test->execute();
}


TEST(ParenTest, notRealArg){
    RBase* test = new Paren(new Executer("NOTREAL"), nullptr);
    test->execute();
}

TEST(ParenTest, parethesis){
    RBase* test = new Paren(new Executer("(echo a && echo b) && echo d"), nullptr);
    test->execute();
}



#endif
