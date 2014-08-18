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

TEST(BIT2D, Random) {
    int H = 500;
    int W = 300;
    int N = 1000;
    BIT2D bit(H, W);
    vector<vector<LL>> grid(H, vector<LL>(W));
    for(int k = 0; k < N; k++) {
        int x = rand() % W;
        int y = rand() % H;
        int w = rand();
        bit.add(x, y, w);
        grid[y][x] += w;

        int a = rand() % W;
        int b = rand() % H;
        LL res = 0;
        for(int i = 0; i <= b; i++) {
            for(int j = 0; j <= a; j++) {
                res += grid[i][j];
            }
        }

        ASSERT_EQ(bit.get(a, b), res);
    }
    LL all = 0;
    for(int y = 0; y < H; y++) {
        for(int x = 0; x < W; x++) {
            all += grid[y][x];
        }
    }
    ASSERT_EQ(bit.get(W - 1, H - 1), all);
}
