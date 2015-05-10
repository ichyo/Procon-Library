// 最小費用流(負辺なし) O(F E logV) {{{
// 使い方:
// /* 頂点の数を指定する */
// MinCostFlow solver(n);
// /* 辺を追加する (始点, 終点, 容量, コスト) */
// solver.add_edge(0, 1, 5, 10);
// /* 最小費用流を求める (始点, 終点, 流量) */ 
// cout << solver.min_cost_flow(0, 1, 5) << endl;
struct MinCostFlow{
    typedef pair<int, int> P; // (最短距離, 頂点の番号)
    static const int INF = 100000000; // infinity

    struct Edge{
        int dst, cap, cost, rev;
        Edge() {}
        Edge(int d, int c, int cs, int r) : 
            dst(d), cap(c), cost(cs), rev(r) {}
    };

    typedef vector<Edge> Node;
    typedef vector<Node> Graph;

    Graph G;

    MinCostFlow(int N) : G(N) {}

    // from から to へ向かう容量cap, 費用costの辺を追加
    void add_edge(int src, int dst, int cap, int cost){
        assert(cost >= 0); // 負の辺は貼れない
        G[src].push_back(Edge(dst, cap, cost, G[dst].size()));
        G[dst].push_back(Edge(src, 0, -cost, G[src].size() - 1));
    }

    // 頂点sから頂点tへの流量fの最小費用流を求める
    // 流せない場合は-1を返す
    int min_cost_flow(int s, int t, int f){
        int V = G.size();
        vector<int> h(V);
        vector<int> prevv(V), preve(V);
        int res = 0;
        while(f > 0){
            // dijkstraでhを更新する (負の辺がある場合は使えない!)
            priority_queue<P, vector<P>, greater<P>> que;
            vector<int> dist(V, INF);
            dist[s] = 0;
            que.push(P(0, s));

            while(!que.empty()){
                P p = que.top(); que.pop();
                int v = p.second;
                if(dist[v] < p.first) continue;
                for(int i = 0; i < G[v].size(); i++){
                    Edge& e = G[v][i];
                    int ndist = dist[v] + e.cost + h[v] - h[e.dst];
                    if(e.cap > 0 && dist[e.dst] > ndist){
                        dist[e.dst] = ndist;
                        prevv[e.dst] = v;
                        preve[e.dst] = i;
                        que.push(P(ndist, e.dst));
                    }
                }
            }

            if(dist[t] == INF){
                // これ以上流せない
                return -1;
            }

            for(int v = 0; v < V; v++) h[v] += dist[v];

            int d = f;
            for(int v = t; v != s; v = prevv[v]){
                d = min(d, G[prevv[v]][preve[v]].cap);
            }

            f -= d;
            res += d * h[t];
            for(int v = t; v != s; v = prevv[v]){
                Edge& e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};
//}}}

// 最小費用流(負辺あり) (not verified) O(F E logV + VE) {{{
// 使い方:
// /* 頂点の数を指定する */
// MinCostFlow solver(n);
// /* 辺を追加する (始点, 終点, 容量, コスト) */
// solver.add_edge(0, 1, 5, 10);
// /* 最小費用流を求める (始点, 終点, 流量) */ 
// cout << solver.min_cost_flow(0, 1, 5) << endl;
struct MinCostFlow2{
    typedef pair<int, int> P; // (最短距離, 頂点の番号)
    static const int INF = 100000000; // infinity

    struct Edge{
        int dst, cap, cost, rev;
        Edge() {}
        Edge(int d, int c, int cs, int r) : 
            dst(d), cap(c), cost(cs), rev(r) {}
    };

    typedef vector<Edge> Node;
    typedef vector<Node> Graph;

    Graph G;

    MinCostFlow2(int N) : G(N) {}

    // from から to へ向かう容量cap, 費用costの辺を追加
    void add_edge(int src, int dst, int cap, int cost){
        G[src].push_back(Edge(dst, cap, cost, G[dst].size()));
        G[dst].push_back(Edge(src, 0, -cost, G[src].size() - 1));
    }

    // 頂点sから頂点tへの流量fの最小費用流を求める
    // 流せない場合は-1を返す
    int min_cost_flow(int s, int t, int f){
        const int n = G.size();
        vector<int> h(n);
        vector<int> prevv(n), preve(n);
        int res = 0;
        bool first_iter = true;
        while(f > 0){
            vector<int> dist(n, INF);
            dist[s] = 0;

            if(first_iter) {
                first_iter = false;
                // SPFA {{{
                vector<bool> inque(n);
                queue<int> que;
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
                // }}}
            } else {
                // dijkstra {{{
                priority_queue<P, vector<P>, greater<P>> que;
                que.push(P(0, s));

                while(!que.empty()){
                    P p = que.top(); que.pop();
                    int v = p.second;
                    if(dist[v] < p.first) continue;
                    for(int i = 0; i < G[v].size(); i++){
                        Edge& e = G[v][i];
                        int ndist = dist[v] + e.cost + h[v] - h[e.dst];
                        if(e.cap > 0 && dist[e.dst] > ndist){
                            dist[e.dst] = ndist;
                            prevv[e.dst] = v;
                            preve[e.dst] = i;
                            que.push(P(ndist, e.dst));
                        }
                    }
                }
                // }}}
            }

            if(dist[t] == INF){
                // これ以上流せない
                return -1;
            }

            for(int v = 0; v < n; v++) h[v] += dist[v];

            int d = f;
            for(int v = t; v != s; v = prevv[v]){
                d = min(d, G[prevv[v]][preve[v]].cap);
            }

            f -= d;
            res += d * h[t];
            for(int v = t; v != s; v = prevv[v]){
                Edge& e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};
//}}}
