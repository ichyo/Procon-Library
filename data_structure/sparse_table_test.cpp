#include "gtest/gtest.h"
#include "./sparse_table.cpp"

TEST(SparseTable, SmallAll1) {
    const int n = 1024;
    vector<int> v(n);
    REP(i, n) v[i] = rand();

    int min_idx[n][n+1] = {};
    REP(i, n) {
        min_idx[i][i+1] = i;
    }

    for(int l = 2; l <= n; l++) {
        for(int i = 0; i+l <= n; i++) {
            const int p = min_idx[i][i+l-1];
            if(v[p] > v[i+l-1]) {
                min_idx[i][i+l] = i+l-1;
            } else {
                min_idx[i][i+l] = p;
            }
        }
    }

    SparseTable<int> rmq(v);

    for(int i = 0; i < n; i++) {
        for(int j = i+1; j <= n; j++) {
            ASSERT_EQ(min_idx[i][j], rmq.query_idx(i, j));
        }
    }
}

TEST(SparseTable, SmallAll2) {
    const int n = 1024 + 1;
    vector<int> v(n);
    REP(i, n) v[i] = rand();

    int min_idx[n][n+1] = {};
    REP(i, n) {
        min_idx[i][i+1] = i;
    }

    for(int l = 2; l <= n; l++) {
        for(int i = 0; i+l <= n; i++) {
            const int p = min_idx[i][i+l-1];
            if(v[p] > v[i+l-1]) {
                min_idx[i][i+l] = i+l-1;
            } else {
                min_idx[i][i+l] = p;
            }
        }
    }

    SparseTable<int> rmq(v);

    for(int i = 0; i < n; i++) {
        for(int j = i+1; j <= n; j++) {
            ASSERT_EQ(min_idx[i][j], rmq.query_idx(i, j));
        }
    }
}

TEST(SparseTable, BenchMarkBuild) {
    const int n = 1e6;
    const int q = 1;
    vector<int> v(n);
    REP(i, n) v[i] = rand();
    SparseTable<int> rmq(v);
    int ans = 0;
    REP(i, q) {
        int b = rand() % n;
        int e = rand() % (n - b) + b+1;
        ans ^= rmq.query(b, e);
    }
}
TEST(SparseTable, BenchMarkAll) {
    const int n = 1e6;
    const int q = 1e6;
    vector<int> v(n);
    REP(i, n) v[i] = rand();
    SparseTable<int> rmq(v);
    int ans = 0;
    REP(i, q) {
        int b = rand() % n;
        int e = rand() % (n - b) + b+1;
        ans ^= rmq.query(b, e);
    }
}
