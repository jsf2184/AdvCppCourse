//
// Created by Jeffrey on 5/11/2018.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../TestedClass.h"

namespace {
    TEST(TestedClassTest, Getter) {
        TestedClass sut(3);
        EXPECT_EQ(3, sut.getX());
    }
}
