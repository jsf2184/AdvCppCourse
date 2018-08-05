#include <iostream>
#include <gtest/gtest.h>
#include <limits>
#include <climits>

using namespace std;


namespace  jsf2184 {

    TEST(ZSEQ_Tests, shiftMask) {
        unsigned int mask = 1;
        unsigned int num_bits = sizeof(unsigned int) * CHAR_BIT;
        cout << "num_bits = " << num_bits << endl;
        for (int i=0; i<num_bits; i++) {
            cout << "i = " << i << " mask: " << mask << endl;
            mask = mask << 1;
        }
    }
    int getLongestZeroSequence(int N) {
        unsigned int mask = 1;
        unsigned int num_bits = sizeof(unsigned int) * CHAR_BIT;
        bool wasOne = false;
        int currentGap = 0;
        int maxGap = 0;

        for (int i=0; i<num_bits; i++) {
            auto maskedVal = N & mask;
            int bit = (maskedVal == 0) ? 0 : 1;

            if (bit) {
                if (currentGap > maxGap) {
                    maxGap = currentGap;
                }
                currentGap = 0;
                wasOne = true;
            } else {
                // got a zero bit
                if (wasOne || currentGap > 0) {
                    currentGap++;
                }
            }
//            cout << "i = " << i
//                 << ", mask = " << mask
//                 << ", maskedVal = " << maskedVal
//                 << ", bit = " << bit
//                 << ", currentGap = " << currentGap
//                 << ", maxGap = " << maxGap<< endl;
            mask = mask << 1;
        }
        cout << "With N = " << N << ", maxGap = " << maxGap << endl;
        return maxGap;
    }

    TEST(ZSEQ_Tests, GetLongest) {
        EXPECT_EQ(4, getLongestZeroSequence(529));
        EXPECT_EQ(2, getLongestZeroSequence(9));
        EXPECT_EQ(1, getLongestZeroSequence(20));
        EXPECT_EQ(0, getLongestZeroSequence(0b001000));
        EXPECT_EQ(4, getLongestZeroSequence(0b00100100001));
        EXPECT_EQ(6, getLongestZeroSequence(0b100000010010001));
    }
}
