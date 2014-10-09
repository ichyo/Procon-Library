#include "../gtest/gtest.h"
#include "./simpson.cpp"

TEST(Simpson, PI) {
    auto f = [&](double x) -> double {
        if(x * x > 1) return 0;
        return sqrt(1 - x * x);
    };

    ASSERT_NEAR(simpson(-1, 1, 10000, f), M_PI / 2.0, 1e-6);
}
