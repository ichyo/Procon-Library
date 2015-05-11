#include "../common/common.h"
#include "../common/graph.h"

typedef unsigned long long ULL;

// 重み付き最大独立集合 (重み付き最大クリーク) 
// ref. https://sites.google.com/site/indy256/algo/bron_kerbosh
//
// BronKerbosch は 極大クリーク を列挙するアルゴリズム
// 補グラフのクリークは 独立集合 に対応するので，
// 重み付き最大独立集合を解くことができる．
//
// verify: AOJ 2403 (0.53 sec) (重み付き最大独立集合)
// (最速は0.03 secなのでそんなに速くない．
// 速さを求めるならちゃんとした枝刈りを書くべき)
//
// verify: 模擬地区予選2014 I問題 (1sec) (極大独立集合列挙)
// (自前DFSが1.7secなので少し速い)

inline int trail0(ULL s) { return (s ? __builtin_ctzll(s) : 64); }

int BronKerbosch(const vector<ULL>& g, ULL cur, ULL allowed, ULL forbidden, const vector<int>& weights) {
    if (allowed == 0 && forbidden == 0) {
        // 極大クリークに対する処理をここに書く
        int res = 0;
        for (int u = trail0(cur); u < g.size(); u += trail0(cur >> (u + 1)) + 1)
            res += weights[u];
        return res;
    }
    if (allowed == 0) return -1;
    int res = -1;
    int pivot = trail0(allowed | forbidden);
    ULL z = allowed & ~g[pivot];
    for (int u = trail0(z); u < g.size(); u += trail0(z >> (u + 1)) + 1) {
        res = max(res, BronKerbosch(g, cur | (1ULL << u), allowed & g[u], forbidden & g[u], weights));
        allowed ^= 1ULL << u;
        forbidden |= 1ULL << u;
    }
    return res;
}

int maximum_clique(const Graph& G, const vector<int>& weights) {
    int n = G.size();
    assert(n < 64);
    vector<ULL> g(n, 0);
    REP(i, n) for(int j : G[i]) g[i] |= (1ULL << j);
    return BronKerbosch(g, 0, (1ULL << n) - 1, 0, weights);
}

int maximum_independet_set(const Graph& G, const vector<int>& weights) {
    int n = G.size();
    assert(n < 64);
    vector<ULL> g(n);
    REP(i, n) REP(j, n) if(i != j) g[i] |= (1ULL << j);
    REP(i, G.size()) for(int j : G[i]) g[i] ^= (1ULL << j);
    return BronKerbosch(g, 0, (1ULL << n) - 1, 0, weights);
}
