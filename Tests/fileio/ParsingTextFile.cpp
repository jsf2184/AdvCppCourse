//
// Section 3 Lesson 9
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

namespace {
    int parse(const string &inputFileName) {
        ifstream inFile;
        inFile.open(inputFileName);
        if (inFile.is_open()) {

            // Lines look like this...
            //   text : number
            //
            string text;
            while (inFile) {
                getline(inFile, text, ':');
                int number;
                inFile >> number;
                // Learned: consumes any whitespace including end of line
                inFile >> ws;
                if (!inFile) {
                    // this prevents us from printing if the >> operator failed.
                    break;
                }
                cout << "text: '" << text << "', number = "  << number << endl;
            }
            inFile.close();
        } else {
            cout << "Cannot open file: " << inputFileName << endl;
            return -1;
        }
        return 0;
    }

    TEST(ParseFileTests, ParseFile) {
        cout << endl;
        int res = parse("parse.txt");
        EXPECT_EQ(0, res);
    }


}
