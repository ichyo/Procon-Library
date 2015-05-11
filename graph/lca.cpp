#include "../common/common.h"
#include "../common/graph.h"

// 最近共通祖先
// 使い方:
// /* コンストラクタ */
// LCA lca(Graph, Root Vertex);
// /* 二つの頂点を指定すると最近共通祖先が返ってくる */
// cout << lca.query(vertex1, vertex2) << endl;

struct LCA{
    int log_v;
    vector<int> depth;
    vector<vector<int>> par;

    void dfs(const Graph& G, int v, int p, int d){
        depth[v] = d;
        par[v][0] = p;
        for(int next : G[v]) if(next != p) {
            dfs(G, next, v, d + 1);
        }
    }

    LCA(const Graph& G, int root) {
        int n = G.size();

        for(log_v = 0; (1 << log_v) < n; log_v++) { }

        depth.resize(n);
        par.assign(n, vector<int>(log_v + 1));

        dfs(G, root, root, 0);

        for(int k = 0; k + 1 <= log_v; k++){
            for(int v = 0; v < n; v++){
                par[v][k + 1] = par[ par[v][k] ][k];
            }
        }
    }

    int query(int u, int v){
        if(depth[u] > depth[v]) swap(u, v);
        for(int k = 0; k <= log_v; k++){
            if((depth[v] - depth[u]) >> k & 1){
                v = par[v][k];
            }
        }
       
        if(u == v) return u;

        for(int k = log_v; k >= 0; k--){
            if(par[u][k] != par[v][k]){
                u = par[u][k];
                v = par[v][k];
            }
        }

        return par[u][0];
    }
};
