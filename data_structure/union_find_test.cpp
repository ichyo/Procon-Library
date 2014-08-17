#include "gtest/gtest.h"
#include "./union_find.cpp"

TEST(UnionFind, Init) {
    int N = 1000000;
    UnionFind uf(N);
    REP(i, N) {
        ASSERT_TRUE(uf.same(i, i));
    }
    REP(i, N) {
        ASSERT_EQ(uf.root(i), i);
    }
    REP(i, N - 1) {
        ASSERT_FALSE(uf.same(0, i + 1));
    }
}

TEST(UnionFind, IsSameUnionFindW) {
    int N = 1000000;
    UnionFind uf(N);
    UnionFindW ufw(N);
    REP(i, N) {
        int x = rand() % N;
        int y = rand() % N;
        uf.unite(x, y);
        ufw.unite(x, y, 0);
        ASSERT_TRUE(uf.same(x, y));
        ASSERT_TRUE(ufw.same(x, y));
        int z = rand() % N;
        int w = rand() % N;
        ASSERT_EQ(uf.same(z, w), ufw.same(z, w));
    }
}
