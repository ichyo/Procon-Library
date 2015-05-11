#include "../common/common.h"
#include "../common/graph_flow.h"
// Dinic O(V^2 E)
// Verify: Many Problems
//
// 使い方:
// /* 頂点の数を指定する */
// Dinic dinic(n);
// /* 辺を張る(始点, 終点, 辺の容量) */
// dinic.add_edge(0, 1, 3);
// dinic.add_edge(1, 2, 2);
// /* 最大流の大きさを出力(始点, 終点) */
// cout << dinic.max_flow(0, 2) << endl;
//
// 注意:
// - max_flow()は副作用としてグラフを変更するので，
//   一度実行するとそれ以降は正しくmax_flowが求まらない．
//
struct Dinic{
    Graph G;
    vector<int> level;
    vector<int> iter;
    
    Dinic(int N) : G(N), level(N), iter(N) {}

    void bfs(int s){
        level.assign(G.size(), -1);
        queue<int> que;
        que.push(s);
        level[s] = 0;
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(const auto& e : G[v]){
                if(e.cap > 0 && level[e.dst] < 0){
                    level[e.dst] = level[v] + 1;
                    que.push(e.dst);
                }
            }
        }
    }

    int dfs(int v, int t, int f){
        if(v == t) return f;
        for(int& i = iter[v]; i < G[v].size(); i++){
            Edge& e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.dst]){
                int d = dfs(e.dst, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.dst][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    void add_edge(int src, int dst, int cap){
        G[src].push_back({dst, cap, (int)G[dst].size()});
        G[dst].push_back({src, 0, (int)G[src].size() - 1});
    }

    int max_flow(int src, int dst){
        int flow = 0;
        while(true){
            bfs(src);
            if(level[dst] < 0) break;
            iter.assign(G.size(), 0);
            while(true){
                int f = dfs(src, dst, INF);
                if(f <= 0) break;
                flow += f;
            }
        }
        return flow;
    }
};

// Ford-Fulkerson
// 計算量: O(FE) 
// Verify: AOJ 2076
struct FordFulkerson{
    Graph G;
    vector<bool> used;
    FordFulkerson(int N) : G(N) {}

    void add_edge(int src, int dst, int cap){
        G[src].push_back({dst, cap, (int)G[dst].size()});
        G[dst].push_back({src, 0, (int)G[src].size() - 1});
    }

    int max_flow(int src, int dst) {
        int flow = 0;
        while(true) {
            used.assign(G.size(), false);
            int f = dfs(src, dst, INT_MAX);
            if(f == 0) break;
            flow += f;
        }
        return flow;
    }

    int dfs(int v, int t, int f) {
        if(v == t) return f;
        used[v] = true;
        for(Edge& e : G[v]) {
            if(e.cap > 0 && !used[e.dst]) {
                int d = dfs(e.dst, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.dst][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};

// Dinic (浮動小数点対応)
// verified: 2014-2015 ACM-ICPC, Asia Xian Regional Contest C: The Problem Needs 3D Arrays
template<typename T>
struct DinicD{
    struct Edge{ 
        int dst;
        T cap;
        int rev;
    };
    static constexpr T EPS = 1e-8;
    static constexpr T INF = numeric_limits<T>::max()/4;
    typedef vector<Edge> Node;
    typedef vector<Node> Graph;
    Graph G;
    vector<int> level;
    vector<int> iter;
    
    DinicD(int N) : G(N), level(N), iter(N) {}

    void bfs(int s){
        level.assign(G.size(), -1);
        queue<int> que;
        que.push(s);
        level[s] = 0;
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(const auto& e : G[v]){
                if(e.cap > EPS && level[e.dst] < 0){
                    level[e.dst] = level[v] + 1;
                    que.push(e.dst);
                }
            }
        }
    }

    T dfs(int v, int t, T f){
        if(v == t) return f;
        for(int& i = iter[v]; i < G[v].size(); i++){
            Edge& e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.dst]){
                T d = dfs(e.dst, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.dst][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    void add_edge(int src, int dst, T cap){
        G[src].push_back({dst, cap, (int)G[dst].size()});
        G[dst].push_back({src, 0, (int)G[src].size() - 1});
    }

    T max_flow(int src, int dst){
        T flow = 0;
        while(true){
            bfs(src);
            if(level[dst] < 0) break;
            iter.assign(G.size(), 0);
            while(true){
                T f = dfs(src, dst, INF);
                if(f < EPS) break;
                flow += f;
            }
        }
        return flow;
    }
};
