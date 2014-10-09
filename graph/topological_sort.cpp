#include "../common/common.h"
#include "../common/graph.h"

bool visit(const Graph &g, int v, vector<int> &order, vector<int> &color) {
    color[v] = 1;
    for(int w : g[v]){
        if (color[w] == 2) continue;
        if (color[w] == 1) return false;
        if (!visit(g, w, order, color)) return false;
    }
    order.push_back(v); color[v] = 2;
    return true;
}
bool topological_sort(const Graph &g, vector<int> &order) {
    int n = g.size();
    vector<int> color(n);
    REP(u, n) if (!color[u] && !visit(g, u, order, color))
        return false;
    reverse(order.begin(), order.end());
    return true;
}
