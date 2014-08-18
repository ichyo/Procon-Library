#include "../common/common.h"

// cf. http://hos.ac/slides/20140319_bit.pdf

// Binary Indexed Tree (Fenwick Tree) (0-indexed)
// two queries in O(log n)
// 1. add w to v[at]
// 2. the sum of v[0], v[1], .., v[at]
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
// 1. add w to v[a], v[a+1], ..., v[b-1]
// 2. get the sum of v[0], v[1], ..., v[c-1]
//
struct BITRange{
    BIT bit0, bit1;
    BITRange(int n) : bit0(n + 1), bit1(n + 1) {}

    // v[a], v[a+1], ..., v[b-1] += by
    void add(int a, int b, LL by) {
        bit0.add(a, -by * a);
        bit0.add(b, +by * b);
        bit1.add(a, by);
        bit1.add(b, -by);
    }

    // v[0] + v[1] + ... + v[c-1]
    LL get(int c) {
        LL A = bit0.get(c);
        LL B = bit1.get(c);
        return A + B * c;
    }
};


