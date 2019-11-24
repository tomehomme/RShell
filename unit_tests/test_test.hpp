#ifndef __TEST_TEST_HPP__
#define __TEST_TEST_HPP__

#include "gtest/gtest.h"

TEST(TestTest, FileDoesntExist){
    RBase* test = new Command("test -e askdhaskjhda");
    test->execute();
}
TEST(TestTest, FileExists){
    RBase* test = new Command("test -e names.txt");
    test->execute();
}
TEST(TestTest, FileExistsNoFlag){
    RBase* test = new Command("test names.txt");
    test->execute();
}
TEST(TestTest, FileDirectoryExists){
    RBase* test = new Command("test -d src");
    test->execute();
}
TEST(TestTest, FileDirectoryDoesntExist){
    RBase* test = new Command("test -d sdhfskdjfhsdf");
    test->execute();
}

TEST(TestTest, BrFileDoesntExist){
    RBase* test = new Command("[ -e askdhaskjhda ]");
    test->execute();
}
TEST(TestTest, BrFileExists){
    RBase* test = new Command("[ test -e names.txt ]");
    test->execute();
}
TEST(TestTest, BrFileExistsNoFlag){
    RBase* test = new Command("[ names.txt ]");
    test->execute();
}
TEST(TestTest, BrFileDirectoryExists){
    RBase* test = new Command("[ -d src ]");
    test->execute();
}
TEST(TestTest, BrFileDirectoryDoesntExist){
    RBase* test = new Command("[ -d sdhfskdjfhsdf ]");
    test->execute();
}
#endif


