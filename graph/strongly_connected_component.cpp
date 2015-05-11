#include "../common/common.h"
#include "../common/graph.h"

// Tarjan's strongly connected components algorithm
// Complexity: O(|V| + |E|)

// two dfs implementation (reference: spaghetti source)
int scc(const Graph& G, const Graph& RG, vector<int>& cmp) {
    int n = G.size();
    int K = 0; // the number of components

    cmp.assign(n, -1); // cmp[v] := component id of vertex v (0, 1, ..., K-1)
    vector<bool> used(n);
    vector<int> order;

    // ordinary dfs
    function<void(int)> dfs = [&](int u) {
        used[u] = true;
        for(int w : G[u]) if(!used[w]) {
            dfs(w);
        }
        order.push_back(u);
    };
    for(int u = 0; u < n; u++) if(!used[u]) {
        dfs(u);
    }
    reverse(order.begin(), order.end());

    // reverse dfs
    function<void(int)> rdfs = [&](int u) {
        cmp[u] = K;
        for(int w : RG[u]) if(cmp[w] == -1) {
            rdfs(w);
        }
    };
    for(int u : order) if(cmp[u] == -1) {
        rdfs(u);
        K++;
    }

    return K;
}

// one dfs implementation (reference: en.wikipedia.org)
int tarjan(const Graph& G, vector<int>& cmp) {
    int n = G.size();
    cmp.assign(n, -1);

    int K = 0;
    int index = 0;
    vector<int> low(n);
    vector<int> id(n);
    vector<int> color(n, 0);
    stack<int> S;

    function<void(int)> dfs = [&](int v) {
        id[v] = low[v] = index++;
        color[v] = 1;
        S.push(v);
        for(int w : G[v]) {
            if(color[w] == 0) {
                dfs(w);
                low[v] = min(low[v], low[w]);
            } else if(color[w] == 1) {
                low[v] = min(low[v], id[w]);
            }
        }

        if(low[v] == id[v]) {
            while(true){
                int w = S.top(); S.pop();
                cmp[w] = K;
                color[w] = 2;
                if(w == v) break;
            }
            K++;
        }
    };

    for(int i = 0; i < n; i++) if(cmp[i] == -1) {
        dfs(i);
    }

    for(int i = 0; i < n; i++) {
        cmp[i] = K - 1 - cmp[i];
    }

    return K;
}

