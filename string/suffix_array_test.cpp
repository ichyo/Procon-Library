#include "gtest/gtest.h"
#include "./suffix_array.cpp"
#include "./SAIS.cpp"

char random_char() {
    const int b = 0x20;
    const int e = 0x7f;
    return (char)(rand() % (e - b) + b);
}
TEST(SAIS_AUNT, LargeRandomTest) {
    int n = 1000000;
    string s(n, 'a');
    REP(i, s.size()) {
        s[i] = random_char();
    }
    auto SAIS = SuffixArray(s);
    auto sa1 = SAIS.array();
    auto sa2 = SA::buildSA(s);
    ASSERT_EQ(sa1, sa2);

    auto Lcp = LCP(s, sa1);
    auto lcp1 = Lcp.array();
    auto lcp2 = SA::buildLCP(s, sa2);
    ASSERT_EQ(lcp1, lcp2);
}
TEST(SAIS, LargeRandomBench) {
    int n = 1000000;
    string s(n, 'a');
    REP(i, s.size()) {
        s[i] = random_char();
    }

    auto SAIS = SuffixArray(s);
    auto sa1 = SAIS.array();

    auto Lcp = LCP(s, sa1);
    auto lcp1 = Lcp.array();
}
TEST(AUNT, LargeRandomBench) {
    int n = 1000000;
    string s(n, 'a');
    REP(i, s.size()) {
        s[i] = random_char();
    }

    auto sa2 = SA::buildSA(s);
    auto lcp2 = SA::buildLCP(s, sa2);
}
