// combination 1
// 計算量: O(MAX_N * MAX_K)
// 制約: n < MAX_N, k < MAX_K
const int MAX_N = 1010;
const int MAX_K = 1010;
LL memo[MAX_N][MAX_K];
LL comb1(int n, int k){
    if(k < 0 || k > n) return 0;
    if(n == 0) return 1;
    if(memo[n][k] > 0) return memo[n][k];
    return memo[n][k] = comb1(n - 1, k - 1) + comb1(n - 1, k);
}

// combination 2
// 前計算: O(MAX_P)
// クエリ処理: O(1)
// 制約: n < MAX_P, k < MAX_P
//       MODは素数
const int MAX_P = 100010;
LL inv[MAX_P];
int fact[MAX_P], rfact[MAX_P];
void init(){
    inv[1] = 1;
    for (int i = 2; i < MAX_P; ++i){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
    fact[0] = rfact[0] = 1;
    for(int i = 1; i < MAX_P; i++){
        fact[i] = ((LL)fact[i - 1] * i) % MOD;
        rfact[i] = ((LL)rfact[i - 1] * inv[i]) % MOD;
    }
}
int comb2(int n, int k){
    return (((LL)fact[n] * rfact[n - k]) % MOD) * rfact[k] % MOD;
}

// ---
// combination (ref. anta's library)
template<int MOD>
struct CombM{
    static const int Mod = MOD;
    typedef ModInt<MOD> mint;
    vector<mint> fact;
    vector<mint> factinv;
    CombM(int N) {
        N = min(N, MOD-1);
        fact.resize(N+1);
        factinv.resize(N+1);
        REP(i, N+1) {
            fact[i] = (i == 0 ? 1 : fact[i-1] * i);
        }
        factinv[N] = fact[N].inv();
        for(int i = N; i >= 1; i--) factinv[i-1] = factinv[i] * i;
    }

    mint nCr(int n, int r) {
        assert(n < (int)fact.size());
        if(n >= MOD) return nCr(n%MOD, r%MOD) * nCr(n/MOD, r/MOD); // Lucas' theorem
        return r > n ? 0 : fact[n] * factinv[n-r] * factinv[r];
    }

    mint nHr(int n, int r) {
        return r == 0 ? 1 : nCr(n+r-1, r);
    }
};
typedef CombM<1000000007> Comb;
