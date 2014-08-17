#include "gtest/gtest.h"
#include "./BIT.cpp"

TEST(BIT, SequentialTest){
    int n = 1000000;
    BIT bit(n);
    for(int i = 0; i < n; i++) {
        bit.add(i, 1);
        ASSERT_EQ(bit.get(i), i + 1);
    }
}

TEST(BIT, SequentialTestLL){
    int n = 1000000;
    BIT bit(n);
    for(int i = 0; i < n; i++) {
        bit.add(i, 1000000);
        ASSERT_EQ(bit.get(i), 1000000LL * (i + 1));
    }
}
