#include "gtest/gtest.h"
#include "./cycle_detection.cpp"

TEST(CYCLE, SmallTest) {
    auto f = [](int x) {
        vector<int> next = {6, 6, 0, 1, 4, 3, 3, 4, 0};
        assert(x >= 0 && x < next.size());
        return next[x];
    };

    pair<int, int> res;

    // 2, 0, 6, 3, 1, 6, 3, 1, 6, 3, 1, ....
    res = cycle_detection(f, 2);
    ASSERT_EQ(2, res.first);
    ASSERT_EQ(3, res.second);

    // 5, 3, 1, 6, 3, 1, 6, ...
    res = cycle_detection(f, 5);
    ASSERT_EQ(1, res.first);
    ASSERT_EQ(3, res.second);

    // 7, 4, 4, 4, 4, ...
    res = cycle_detection(f, 7);
    ASSERT_EQ(1, res.first);
    ASSERT_EQ(1, res.second);

    // 4, 4, 4, ...
    res = cycle_detection(f, 4);
    ASSERT_EQ(0, res.first);
    ASSERT_EQ(1, res.second);
}

