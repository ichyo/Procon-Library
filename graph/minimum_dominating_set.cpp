#include "../common/common.h"
// 支配集合問題 ref. Operafan library
// Verify: AOJ 1015
//
// N(u) = {u} \cup {v | (u, v) \in E} とする
// 支配集合問題とは，頂点集合 S の 要素 v の N(v) の集合和 が
// V と一致するような S のうち最小のものを求める問題．
//
// 別の言葉で言い換えると，グラフの点を選んで，
// 自分自身と，その点に接続している点に色を塗るような操作を考えたとき，
// グラフのすべての点を塗るために必要な操作の最小回数を求める問題．
//
// 支配集合問題はNP完全であることが知られている．
// 以下のコードは，支配集合問題をバックトラックで解く．
// |V| <= 40 程度なら解ける．
//
// 入力Gは以下を満たすようにする
//     G[u][v] := u から v に辺がつながっているかどうか 
//     (有向グラフの場合はVerifyしていない)
//
// 計算量: O(2^|V|) ( |V| <= 40 程度ならOK )
typedef vector<bool> Array;
typedef vector<Array> Matrix;

int dfs(int n, int k, LL G[], LL cover[], int ord[], LL now, int ans, int &bound){
    if(ans >= bound) {
        return bound;
    }
    if(now == (1LL << n) - 1) {
        return bound = ans;
    }
    if(k >= n) {
        return bound;
    }
    if((now | cover[k]) != (1LL << n) - 1) {
        return bound;
    }

    int u = ord[k];
    if((now & G[u]) == G[u]) {
        return dfs(n, k + 1, G ,cover, ord, now, ans, bound);
    }

    return min(dfs(n, k + 1, G ,cover, ord, now | G[u], ans + 1, bound),
            dfs(n, k + 1, G ,cover, ord, now, ans, bound));
}

int dominating_set(const Matrix &G){
    int N = G.size();
    LL M[N];
    memset(M, 0, sizeof(M));
    int cnt[N];
    REP(i, N){
        M[i] = 1 << i;
        cnt[i] = 1;
        REP(j, N) if(G[i][j]){
            M[i] |= 1 << j;
            cnt[i] ++;
        }
    }
    int ord[N];
    REP(i, N) ord[i] = i;

    // sort
    REP(i, N) REP(j, N - 1){
        if(cnt[ord[j]] < cnt[ord[j+1]]){
            swap(ord[j], ord[j+1]);
        }
    }

    LL cover[N + 1];
    cover[N] = 0;
    for(int i = N - 1; i >= 0; i--) {
        cover[i] = cover[i + 1] | M[ord[i]];
    }

    int bound = N;
    return dfs(N, 0, M, cover, ord, 0, 0, bound);
}
