#include "../common/common.h"

// Binary Indexed Tree (Fenwick Tree) (0-indexed)
// two queries in O(log n)
// 1. add w to v[at]
// 2. the sum of v_0, v_1, .., v_at
struct BIT{
    vector<LL> sums;
    BIT(int n) : sums(n) {}

    // v[at] += by
    void add(int at, LL by) {
        while(at < sums.size()){
            sums[at] += by;
            at |= at + 1;
        }
    }

    // v[0] + ... + v[at]
    LL get(int at) {
        LL res = 0;
        while(at >= 0) {
            res += sums[at];
            at = (at & (at + 1)) - 1;
        }
        return res;
    }
};

// BIT (range-version) (0-indexed)
// two queries in O(log n)
// 1. add w to v_a, v_{a + 1}, ..., v_b
// 2. get the sum of v_0, v_1, ..., v_{c - 1}


