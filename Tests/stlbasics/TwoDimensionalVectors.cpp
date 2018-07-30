//
// Section 4 Lesson 14 - Two Dimensional Vectors
//



#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

namespace {

    void populate0(vector<vector<int>> &grid, int rows, int columns) {
        for (int i=0; i<rows; i++) {
            vector<int> vec;
            for (int j=0; j<columns; j++) {
                auto val = (i * 10) + j;
                vec.push_back(val);
            }
            grid.push_back(vec);
        }
    }



    void print0(vector<vector<int>> &grid) {
        cout << endl << "print0(): size = "<< grid.size() << endl;
        for (auto rowIt = grid.cbegin(); rowIt < grid.cend(); rowIt++) {
            for (auto colIt = rowIt->cbegin(); colIt < rowIt->cend(); colIt++) {
                cout << *colIt << " ";
            }
            cout << endl;
        }
    }

    void print1(vector<vector<int>> &grid) {
        cout << endl << "print1(): size = "<< grid.size() << endl;
        for (auto r = 0; r < grid.size(); r++) {
            for (ulong c = 0; c < grid[r].size(); c++) {
                cout << grid[r].at(c) << endl;
            }
        }
    }

    void print2(vector<vector<int>> &grid) {
        cout << endl << "print2(): size = "<< grid.size() << endl;
        for (auto r = 0; r < grid.size(); r++) {
            for (ulong c = 0; c < grid[r].size(); c++) {
                cout << grid[r][c] << endl;
            }
        }
    }

    void print3(vector<vector<int>> &grid) {
        cout << endl << "print3(): size = "<< grid.size() << endl;
        for (auto r = 0; r < grid.size(); r++) {
            vector<int> &row = grid[r];
            for (ulong c = 0; c < row.size(); c++) {
                cout << row[c] << endl;
            }
        }
    }

    void pruneOdds0(vector<vector<int>> &grid) {
        for (auto rowIt = grid.begin(); rowIt < grid.end(); rowIt++) {
            for (auto colIt = rowIt->begin(); colIt < rowIt->end(); colIt++) {
                auto val = *colIt;
                if (val %2 == 1) {
                    colIt = rowIt->erase(colIt);
                }
            }
        }
    }

    void pruneOdds1(vector<vector<int>> &grid) {
        for (auto rowIt = grid.begin(); rowIt < grid.end(); rowIt++) {
            vector<int> &row = *rowIt;
            vector<int>::iterator newEnd =  remove_if(row.begin(), row.end(), [] (int v) {return v % 2 == 1;});
            row.erase(newEnd, row.end());
        }
    }


    TEST(TwoDimVectors, BasicTest) {
        cout << endl;
        vector<vector<int>> grid;
        populate0(grid, 6, 4);
        print0(grid);
        print1(grid);
        print2(grid);
        print3(grid);
    }

    TEST(TwoDimVectors, PruneOdds0) {
        cout << endl;
        vector<vector<int>> grid;
        populate0(grid, 10, 10);
        print0(grid);
        cout << endl << "After odds pruned out" << endl;
        pruneOdds0(grid);
        print0(grid);
    }

    TEST(TwoDimVectors, PruneOddsLambda) {
        cout << endl;
        vector<vector<int>> grid;
        populate0(grid, 10, 10);
        print0(grid);
        pruneOdds1(grid);
        cout << endl << "After odds pruned out" << endl;
        print0(grid);
    }


    TEST(TwoDimVectors, ConstructorTest) {
        cout << endl;
        // grid has 5 vectors in it, each with 3 columns equal to the value 8.
        vector<vector<int>> grid(5, vector<int>(3, 8));
        print0(grid);
    }



}
