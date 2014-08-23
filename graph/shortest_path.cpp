#include "../common/common.h"
#include "../common/graph.h"

// Bellman-Foard
// Complexity: O(VE)
//
// 注意
// - 負の辺があっても問題ない
// - 負閉路がある場合は-INFのリストが返される
vector<int> bellmanford(const Graph& G, int s){
    int n = G.size();
    vector<int> dist(n, INF);
    
    dist[s] = 0;
    REP(iter, n) {
        bool update = false;
        for(int i = 0; i < n; i++) {
            for(Edge e : G[i]) {
                if(dist[i] != INF && dist[e.dst] > dist[i] + e.cost) {
                    dist[e.dst] = dist[i] + e.cost;
                    update = true;
                }
            }
        }
        // 更新が完了したときに最短路が求まる
        if(!update) return dist;
    }

    // n回更新が起きたときは負の閉路が存在
    return vector<int>(n, -INF);
}

// Shortest Path Faster Algorithm (SPFA)
// Compexity: O(VE) (for random graph: O(E))
//
// 注意
// - 負の辺があっても問題ない
// - 負閉路がある場合無限ループする
vector<int> SPFA(const Graph& G, int s) {
    int n = G.size();
    vector<int> dist(n, INF);
    vector<bool> inque(n);
    queue<int> que;

    dist[s] = 0;
    que.push(s);
    inque[s] = true;
    while(!que.empty()){
        int v = que.front();
        que.pop();
        inque[v] = false;
        for(Edge e : G[v]) {
            if(dist[e.dst] > dist[v] + e.cost) {
                dist[e.dst] = dist[v] + e.cost;
                if(!inque[e.dst]) {
                    que.push(e.dst);
                    inque[e.dst] = true;
                }
            }
        }
    }
    return dist;
}

// Dijkstra
// Compexity: // O((E + V) log V)
//
// 注意
// - 負の辺がある場合は利用できない．
vector<int> dijkstra(const Graph& G, int s){
    typedef pair<int, int> P;
    priority_queue<P, vector<P>, greater<P>> que;
    vector<int> dist(G.size(), INF);
    que.push(P(0, s));
    dist[s] = 0;
    while(!que.empty()){
        P p = que.top(); que.pop();
        int v = p.second, c = p.first;
        if(c > dist[v]) continue;
        for(auto& e : G[v]){
            if(dist[e.dst] > dist[v] + e.cost){
                dist[e.dst] = dist[v] + e.cost;
                que.push(P(dist[e.dst], e.dst));
            }
        }
    }
    return dist;
}

