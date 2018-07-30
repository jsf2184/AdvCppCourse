#include <iostream>
#include <string>
#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

bool readFile(const string &inputFileName) {
    ifstream inFile;
    inFile.open(inputFileName);
    if (inFile.good()) {
        std::string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Cannot open file: " << inputFileName << endl;
    }

    return 0;
}



int main(int argc, char **argv) {

    cout << "Running main() from gtest_main.cc" << endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
