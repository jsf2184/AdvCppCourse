#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;



int main(int argc, char **argv) {
    cout << "Running main() from gtest_main.cc" << endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
