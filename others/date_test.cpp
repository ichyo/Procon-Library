#include "../gtest/gtest.h"
#include "./date.cpp"

TEST(DATE, First){
    ASSERT_EQ(1, days(1, 1, 1));
}

TEST(DATE, Today){
    ASSERT_EQ(5, days(2014, 10, 10) % 7);
}
