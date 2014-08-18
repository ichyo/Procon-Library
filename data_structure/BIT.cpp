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

    // --- optional ---
    int size() const { return sums.size(); }
    LL operator [](int idx) const { return sums[idx]; }
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

// BIT (2D-version) (0-indexed)
// two queries in O(logw * lowh)
// 1. add w to v[y][x]
// 2. get the sum of 
// v[0][0], ..., v[0][a], 
// v[1][0], ..., v[1][a], 
// ...
// v[b][0], ..., v[b][a]
struct BIT2D{
    typedef vector<LL> vec;
    vector<vec> sums;
    int H, W;

    BIT2D(int h, int w) : sums(h, vec(w)), H(h), W(w) {}

    // v[y][x] += w
    void add(int x, int y, int w) {
        for(int i = y; i < H; i |= i + 1) {
            for(int j = x; j < W; j |= j + 1) {
                sums[i][j] += w;
            }
        }
    }

    // for y in [0, b]:
    //     for x in [0, a]:
    //         ret += v[y][x]
    LL get(int a, int b) {
        LL res = 0;
        for(int i = b; i >= 0; i = (i & (i + 1)) - 1){
            for(int j = a; j >= 0; j = (j & (j + 1)) - 1){
                res += sums[i][j];
            }
        }
        return res;
    }
};

// Integer set implemented by BIT
// Time: O(log n)
// operation:
// 1. insert 
// 2. erase
// 3. nth_element
// 4. index (nth_element(index(x)) == x)
// 5. etc
struct BITSet{
    BIT bit;
    BITSet(int n) : bit(n) {}
    bool insert(int x) {
        if(count(x) == 1) return false;
        bit.add(x, +1);
        return true;
    }

    bool erase(int x) {
        if(count(x) == 0) return false;
        bit.add(x, -1);
        return true;
    }

    int size() {
        return bit.get(bit.size() - 1);
    }

    void clear() {
        bit = BIT(bit.size());
    }

    int operator[](int idx) {
        if(idx < 0 || idx >= size()) return -1;
        idx ++;
        int x = -1;
        int k = 1;
        while(2 * k < bit.size()){
            k *= 2;
        }
        while(k > 0) {
           if(x + k < bit.size() && bit[x + k] < idx) {
                idx -= bit[x + k];
                x += k;
            }
            k >>= 1;
        }
        return x + 1;
    }

    int index(int x) {
        if(!count(x)) return -1;
        return bit.get(x) - 1;
    }

    int count(int x) {
        return bit.get(x) - bit.get(x - 1);
    }
};
