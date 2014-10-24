#include "../common/common.h"
// 最大二部マッチング O(E sqrt(V))
// /* 左側の頂点の数と右側の頂点の数を指定する */
// Bipartitematching solver(number_of_leftnodes, number_of_rightnodes)
// /* 辺を追加する
// (左側の頂点のindex(0からV1-1), 右側の頂点のindex(0からV2-1)) */
// solver.add_edge(0, 0);
// solver.add_edge(0, 1);
// solver.add_edge(1, 1);
// /* 最大マッチングの大きさを出力する
// // cout << solver.matching() << endl;
// Verified: SPOJ Fast Maximum Matching(2.66 sec)

struct BipartiteMatching{
    typedef vector<int> Node;
    typedef vector<Node> Graph;

    const int V1, V2, V;
    const int NIL;
    Graph G;
    vector<int> match;
    vector<int> level;

    BipartiteMatching(int V1_, int V2_) :
        V1(V1_), V2(V2_), V(V1 + V2), NIL(V), G(V), match(V + 1), level(V + 1) {}

    void add_edge(int u, int v){
        G[u].push_back(v + V1);
    }

    bool bfs(){
        queue<int> que;
        REP(i, V1) {
            if(match[i] == NIL){
                level[i] = 0;
                que.push(i);
            }else{
                level[i] = INF;
            }
        }
        level[NIL] = INF;

        while(!que.empty()){
            int v = que.front(); que.pop();
            if(level[v] < level[NIL]){
                REP(i, G[v].size()){
                    int u = match[G[v][i]];
                    if(level[u] == INF){
                        level[u] = level[v] + 1;
                        que.push(u);
                    }
                }
            }
        }
        return level[NIL] != INF;
    }

    bool dfs(int v){
        if(v == NIL) return true;

        for(int u : G[v]){
            if(level[match[u]] == level[v] + 1 && dfs(match[u])){
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
        level[v] = INF;
        return false;
    }

    int matching(){
        REP(i, G.size()) match[i] = NIL;

        int res = 0;
        while(bfs()){
            for(int v = 0; v < V1; v++){
                if(match[v] == NIL && dfs(v)){
                    res++;
                }
            }
        }
        return res;
    }
};
