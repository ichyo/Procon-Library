#include "../common/common.h"
typedef vector<LL> Array;
typedef vector<Array> Matrix;

// 行列の掛け算 O(N * M * S)
Matrix mul(const Matrix& a, const Matrix& b){
    int N = a.size(), M = b[0].size(), S = a[0].size();
    assert(S == b.size());
    Matrix c(N, Array(M));
    REP(i, N) REP(k, S) REP(j, M) {
        c[i][j] += a[i][k] * b[k][j];
        c[i][j] %= MOD;
    }
    return c;
}
// 正方行列の累乗 O(N^3 * logn)
Matrix pow(Matrix a, LL b){
    int N = a.size();
    Matrix c(N, Array(N));
    REP(i, N) c[i][i] = 1;
    while(b > 0){
        if(b & 1) c = mul(c, a);
        a = mul(a, a);
        b >>= 1;
    }
    return c;
}

