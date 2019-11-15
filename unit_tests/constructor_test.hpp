#ifndef __CONSTRUCTOR_TEST_HPP__
#define __CONSTRUCTOR_TEST_HPP__

#include "gtest/gtest.h"
#include "../src/Command.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"


TEST(ConstructorTest, Command){
    RBase* test = new Command("ls");
    test->print();
    cout << endl;
}

TEST(ConstructorTest, And){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new And(left, right);
    test->print();
    cout << endl;
}

TEST(ConstructorTest, Or){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new Or(left, right);
    test->print();
    cout << endl;
}

#endif

