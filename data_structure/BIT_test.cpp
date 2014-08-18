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

TEST(BITRange, Random) {
    int n = 10000;
    vector<LL> sum(n);
    BITRange bit(n);
    int x, y, w;
    for(int i = 0; i < n; i++) {
        x = rand() % (n - 1) + 1;
        y = rand() % x;
        w = rand();
        swap(x, y);
        for(int j = x; j <= y; j++) {
            sum[j] += w;
        }
        bit.add(x, y + 1, w);

        x = rand() % n;
        LL res = 0;
        for(int j = 0; j <= x; j++) {
            res += sum[j];
        }

        ASSERT_EQ(bit.get(x + 1), res);
    }
}
