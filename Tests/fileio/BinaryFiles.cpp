//
// Section 3 Lesson 11
//

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

using namespace std;

namespace {

#pragma pack(push, 1)
    struct PersonA {
        char name[50];
        int age;
        double weight;
    };
#pragma pack(pop)

    struct PersonB {
        char name[50];
        int age;
        double weight;
    };

     PersonA aPeople[] {
            {"JoeA", 21, 210},
            {"BobA", 22, 220}
    };
    static PersonB bPeople[] {
            {"JoeB", 21, 210},
            {"BobB", 22, 220}
    };

    void printPerson(const string &label, const PersonA &person) {
        cout << label << " name: '" << person.name << "', age: " << person.age << ", weight: " << person.weight << endl;
    }

    void printArray(const string &label, PersonA people[], int num) {
        for (int i=0; i<num; i++) {
            printPerson(label, people[i]);
        }
    }

    void printPerson(const string &label, const PersonB &person) {
        cout << label <<  " name: '" << person.name << "', age: " << person.age << ", weight: " << person.weight << endl;
    }

    void printArray(const string &label, PersonB people[], int num) {
        for (int i=0; i<num; i++) {
            printPerson(label, people[i]);
        }
    }


    ofstream openOutfile(const string &fileName) {
        ofstream res;
        res.open(fileName, ios_base::binary);
        return res;
    }

    ifstream openInfile(const string &fileName) {
        ifstream res;
        res.open(fileName, ios_base::binary);
        return res;
    }


    bool writeFile(const char *ptr, int size, ofstream &outputFile, bool closeIt) {
        if (!outputFile.is_open()) {
            return false;
        }
        outputFile.write(ptr, size);
        if (closeIt) {
            outputFile.close();
        }
    }

    bool writeFile(const string &fileName, char *ptr, int size) {
        ofstream outputFile = openOutfile(fileName);
        return writeFile(ptr, size, outputFile, true);
    }

    bool readFile(char *ptr, int size, ifstream &inputFile, bool closeIt) {
        if (!inputFile.is_open()) {
            return false;
        }
        inputFile.read(ptr, size);
        if (closeIt) {
            inputFile.close();
        }
    }

    bool readFile(const string &fileName, char *ptr, int size) {
        ifstream inputFile = openInfile(fileName);
        return readFile(ptr, size, inputFile, true);
    }

    TEST(BinaryFileTests, SimpleSize) {
        cout << endl;
        cout << "PersonA: structSize=" <<  sizeof(PersonA) << ", arraySize=" << sizeof(aPeople) << ", elemSize=" << sizeof(aPeople[0]) << endl;
        cout << "PersonB: structSize=" <<  sizeof(PersonB) << ", arraySize=" << sizeof(bPeople) << ", elemSize=" << sizeof(bPeople[0]) << endl;
    }

    TEST(BinaryFileTests, RWStructA) {
        cout << endl;
        writeFile("oneA.bin", reinterpret_cast<char *>( &aPeople[0]), sizeof(PersonA));
        PersonA personA;
        readFile("oneA.bin", reinterpret_cast<char *>(&personA), sizeof(personA) );
        printPerson("src", aPeople[0]);
        printPerson("res", personA);
    }

    TEST(BinaryFileTests, RWArrayA) {
        cout << endl;
        writeFile("arrayA.bin", reinterpret_cast<char *>( &aPeople[0]), sizeof(aPeople));
        PersonA people[2];
        readFile("arrayA.bin", reinterpret_cast<char *>(&people[0]), sizeof(aPeople) );
        printArray("src", aPeople, 2);
        printArray("res", people, 2);
    }

    TEST(BinaryFileTests, RWStructB) {
        cout << endl;
        writeFile("oneB.bin", reinterpret_cast<char *>( &bPeople[0]), sizeof(PersonB));
        PersonB personB;
        readFile("oneB.bin", reinterpret_cast<char *>(&personB), sizeof(personB) );
        printPerson("src", bPeople[0]);
        printPerson("res", personB);
    }
    TEST(BinaryFileTests, RWArrayB) {
        cout << endl;
        writeFile("arrayB.bin", reinterpret_cast<char *>( &bPeople[0]), sizeof(bPeople));
        PersonB people[2];
        readFile("arrayB.bin", reinterpret_cast<char *>(&people[0]), sizeof(bPeople) );
        printArray("src", bPeople, 2);
        printArray("res", people, 2);
    }



}




