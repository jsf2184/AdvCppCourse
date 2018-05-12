//
// Created by Jeffrey on 5/11/2018.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../TestedClass.h"

using namespace std;
namespace {

class MyFixture : public ::testing::Test {
    public:
        MyFixture() {
            cout << "MyFixture constructor()" << endl;
        }
    };
    TEST_F(MyFixture, Getter) {
        TestedClass sut(3);
        EXPECT_EQ(3, sut.getX());
    }
    TEST_F(MyFixture, Getter2) {
        TestedClass sut(4);
        EXPECT_EQ(4, sut.getX());
    }
}
