#include "../common/common.h"
// 最大二部マッチング O(VE)
//
// /* 頂点の数を指定 */
// BipartiteMatching solver(n);
//
// /* 枝を追加 */
// solver.add_edge(0, 1);
//
// /* 最大マッチングの大きさを出力 */
// cout << solver.matching() << endl; // -> 1
//
// /* マッチングの相手を出力 */
// cout << solver.match[0] << endl; // -> 1
//
// Verify: RUPC 2014 day2 Problem G
struct BipartiteMatching{
    typedef vector<int> Node;
    typedef vector<Node> Graph;

    Graph G;
    vector<int> match;
    vector<bool> used;

    BipartiteMatching(int N) : G(N) {}

    void add_edge(int u, int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bool dfs(int u){
        used[u] = true;
        for(int v : G[u]){
            int w = match[v];
            if(w < 0 || (!used[w] && dfs(w))){
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int matching(){
        int res = 0;
        match.assign(G.size(), -1);
        for(int u = 0; u < G.size(); u++){
            if(match[u] < 0){
                used.assign(G.size(), false);
                if(dfs(u)) res++;
            }
        }
        return res;
    }
};
