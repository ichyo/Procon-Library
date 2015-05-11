#include "../common/common.h"

// v[l] + v[l+1] + ... + v[r-1] を定数時間で計算する
// l >= r のときは [l, n) + [0, r) の和を返す
struct CumSum {
    typedef long long Sum;
    vector<Sum> v;

    template<typename T>
    CumSum(const vector<T>& a): v(a.size()+1) {
        for(size_t i = 0; i < a.size(); i++) {
            v[i+1] = v[i] + a[i];
        }
    }

    // [l, r)
    inline Sum get(int l, int r) const {
        return v[r] - v[l] + (l >= r ? v.back() : 0);
    }
};

