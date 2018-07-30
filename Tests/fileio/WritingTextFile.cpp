//
// Section 3 Lesson 7
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

namespace  {

    int writeFile(const string &outputFileName) {

        fstream outFile;

        outFile.open(outputFileName, ios::out);

        if(outFile.is_open()) {
            outFile << "Hello there" << endl;
            outFile << 123 << endl;
            outFile.close();
        }
        else {
            cout << "Could not create file: " << outputFileName << endl;
            return -1;
        }

        return 0;
    }
    

    TEST(FileWriteTests, WriteOne) {
        int res = writeFile("test.txt");
        EXPECT_EQ(0, res);
    }


}
