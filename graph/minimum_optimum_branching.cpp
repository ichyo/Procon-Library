// 最小全域有向木(Edmonds' algorithm) O(VE)
// (強連結成分分解が必要)
// (グラフが壊されることに注意)
// 注意: 入力のグラフが自己辺を含むときに正しく動かない．
// Verified: AOJ 2309, UVA 11183
//
// 注意: 強連結成分分解を重み付きversionに書き換える必要あり．
struct Edge{
    int src, dst, cost;
};
typedef vector<Edge> Node;
typedef vector<Node> Graph;
int MOB(Graph& G, int root){
    int V = G.size();
    int res = 0;

    // 各ノードに入る最小の辺を求める
    vector<Edge> min_edge(V, {-1, -1, INF});
    REP(v, V) REP(i, G[v].size()){
        Edge& e = G[v][i];
        if(min_edge[e.dst].cost > e.cost){
            min_edge[e.dst] = e;
        }
    }

    // コストを足し合わせる
    REP(v, V) if(v != root) {
        if(min_edge[v].cost == INF) return INF; // rootから到達不可能な頂点が存在する
        res += min_edge[v].cost;
    }

    // 各辺のコストを、最小のコスト分だけ減らす
    REP(v, V) REP(i, G[v].size()){
        Edge& e = G[v][i];
        if(e.dst != root) e.cost -= min_edge[e.dst].cost;
    }

    // 強連結成分分解で、ループがあるかどうか調べる
    Graph sG(V);
    Graph sGR(V);
    REP(v, V) if(v != root) {
        Edge& e = min_edge[v];
        sG[e.src].push_back(e);
        sGR[e.dst].push_back({e.dst, e.src, e.cost});
    }
    vector<int> comp;
    int m = scc(sG, sGR, comp); // 強連結成分分解
    if(m == V) return res; // ループがなければ終了

    // 成分の間に辺を張った新しいグラフを作る
    Graph nG(m);
    REP(v, V) REP(i, G[v].size()){
        Edge& e = G[v][i];
        if(comp[v] != comp[e.dst]) nG[comp[v]].push_back({comp[v], comp[e.dst], e.cost});
    }
    return min(INF, res + MOB(nG, comp[root]));
}
