#include "../common/common.h"
#include "../common/graph_weight.h"

// ベルマンフォード
// 概要:
// sを始点とした各頂点への最短距離をリストで返す
// ダイクストラと違い，負の辺があっても正しく動く
// 負の閉路があるときは-INFで埋められたリストを返す
// 計算量:
// O(VE)
vector<int> bellman_ford(const Graph& G, int s){
    int V = G.size();
    vector<int> dist(V, INF);
    dist[s] = 0;
    for(int iter = 0; iter < V; iter++){
        bool update = false;
        REP(u, V) if(dist[u] != INF) for(auto& e : G[u]){
            if(dist[e.dst] > dist[u] + e.cost){
                dist[e.dst] = dist[u] + e.cost;
                update = true;
            }
        }
        // 更新が完了したときに最短路が求まる
        if(!update) return dist;
    }
    // V回更新が起きたときは負の閉路が存在する
    return vector<int>(V, -INF);
}
