#include "../common/common.h"

template<typename T, typename Comp=less<T>>
class SparseTable{
private:
    Comp comp;
    int N, K;
    vector<T> value;
    vector<vector<int>> idx;

    inline int log2(int x) {
        return 31 - __builtin_clz(x);
    }

public:
    SparseTable(const vector<T>& v) : value(v) {
        N = v.size();
        K = log2(N) + 1;

        idx.resize(K);
        idx[0].resize(N);
        REP(i, N) idx[0][i] = i;

        for(int log = 0; log+1 < K; log++) {
            const int L = N+1 - (1<<(log+1));
            idx[log+1].resize(L);
            for(int i = 0; i < L; i++) {
                const int p = idx[log][i];
                const int q = idx[log][i+(1<<log)];
                idx[log+1][i] = (comp(v[p], v[q]) ? p : q);
            }
        }
    }

    // return index of minimum/maximum value in v[b], ..., v[e-1]
    int query_idx(int b, int e) {
        const int log = log2(e-b);
        const int p = idx[log][b];
        const int q = idx[log][e-(1<<log)];
        return (comp(value[p], value[q]) ? p : q);
    }

    // return minimum/maximum value in v[b], ..., v[e-1]
    int query(int b, int e) {
        return value[query_idx(b, e)];
    }
};
