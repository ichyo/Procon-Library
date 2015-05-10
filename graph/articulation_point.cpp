// 関節点・橋 (ref. natsugiri's code)
class ArticulationPoint {
// ArticulationPoint {{{
    vector<int> ord, low, art;
    int cnt;
    vector<pair<int, int> > _bridges; 

    void dfs(const Graph&G, int v, int p) {
        ord[v] = low[v] = cnt++;
        for(int i = 0; i < G[v].size(); i++) {
            int w = G[v][i];
            if(ord[w] == -1) {
                dfs(G, w, v);
                low[v] = min(low[v], low[w]);
                if(ord[v] <= low[w]) art[v]++;

                // remove this line if you don't use bridges()
                if(ord[v] <  low[w]) _bridges.push_back(make_pair(min(v, w), max(v, w)));
            } else if(w != p) {
                low[v] = min(low[v], ord[w]);
            }
        }
    }

public:
    // }}}
    // Time complexity: O(V + E)
    ArticulationPoint(const Graph& G) {
        int n = G.size();
        cnt = 0;
        ord.assign(n, -1);
        low.assign(n, 0);
        art.assign(n, 0);
        for(int i = 0; i < n; i++) {
            if(ord[i] == -1) {
                dfs(G, i, -1);
                if (art[i]) art[i]--;
            }
        }
    }

    // return whether (v, w) is a bridge or not. (verified: AOJ1350)
    bool is_bridge(int v, int w) { return ord[v] < low[w] || ord[w] < low[v]; }

    // return all bridges. (not verified)
    const vector<pair<int, int>>& bridges() { return _bridges; }

    // return whether v is a articulation point or not. (not verified)
    bool is_art(int v) { return art[v] > 0; }

    // return how many number of connected components are increased if we remove a vertex v. (not verified)
    int inc_CC(int v) { return art[v]; }
};
