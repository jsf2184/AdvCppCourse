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

    void printStrings(vector<string> &strings) {
        unsigned long numStrings = strings.size();
        cout << "printing vector of size " << numStrings << endl;
        for (int i=0; i < numStrings; i++) {
            cout << strings[i] << endl;
        }
    }

    bool readFile0(const string &inputFileName, vector<string> &strings) {
        ifstream inFile;
        inFile.open(inputFileName);
        if (inFile.is_open()) {
            string line;

            // Learned: operator overloading (not sure yet which one) causes (inFile) to
            // return a boolean.
            //
            while (inFile) {
                getline(inFile, line);
                strings.push_back(line);
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Cannot open file: " << inputFileName << endl;
            return -1;
        }
        return 0;
    }

    bool readFile1(const string &inputFileName, vector<string> &strings) {
        ifstream inFile;
        inFile.open(inputFileName);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                strings.push_back(line);
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Cannot open file: " << inputFileName << endl;
            return -1;
        }
        return 0;
    }

    bool readFile2(const string &inputFileName, vector<string> &strings) {
        ifstream inFile;
        inFile.open(inputFileName);
        if (inFile.is_open()) {
            string line;
            // Note: this does not produce the same results as readFile1() above because
            // spaces delimit the normal behavior of >>. THus, 'a b c' on a single line
            // results in the 3 values 'a' 'b' 'c' being set to line in distinct iterations.
            //
            while (inFile >> line) {
                strings.push_back(line);
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Cannot open file: " << inputFileName << endl;
            return -1;
        }
        return 0;
    }


    TEST(FileReadTests, ReadFile0) {
        cout << endl;
        vector<string> strings;
        int res = readFile0("test.txt", strings);
        printStrings(strings);
        EXPECT_EQ(0, res);
    }


    TEST(FileReadTests, ReadFile1) {
        cout << endl;
        vector<string> strings;
        int res = readFile1("test.txt", strings);
        printStrings(strings);
        EXPECT_EQ(0, res);
    }

    TEST(FileReadTests, ReadFile2) {
        cout << endl;
        vector<string> strings;
        int res = readFile2("test.txt", strings);
        printStrings(strings);
        EXPECT_EQ(0, res);
    }

}
