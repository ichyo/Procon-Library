#include "../common/common.h"

// 座標圧縮。大小関係を保ったまま、[0, 種類数)の範囲に値を変換する。
// 返り値は値の種類数。
template<typename T>
int compress(vector<T>& v) {
    vector<T> x(v);
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());

    map<T, int> m;
    for(size_t i = 0; i < x.size(); i++) {
        m[x[i]] = i;
    }

    for(size_t i = 0; i < v.size(); i++) {
        v[i] = m[v[i]];
    }

    return x.size();
}
