#ifndef __CONSTRUCTOR_TEST_HPP__
#define __CONSTRUCTOR_TEST_HPP__

#include "gtest/gtest.h"
#include "../src/Command.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Semi.cpp"

TEST(ConstructorTest, Command){
    RBase* test = new Command("ls");

}

TEST(ConstructorTest, And){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new And(left, right);
}

TEST(ConstructorTest, Or){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new Or(left, right);
}

TEST(ConstructorTest, Semi){
    RBase* left = new Command("echo");
    RBase* right = new Command("ls");
    RBase* test = new Semi(left, right);
   
}

#endif

