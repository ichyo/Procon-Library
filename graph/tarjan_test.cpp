#include "tarjan.cpp"
#include "../gtest/gtest.h"

Graph random(int n, int e) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n-1);
    vector<set<int>> m(n);
    Graph G(n);
    for(int i = 0; i < e; i++) {
        int a, b;
        while(true){
            a = dis(gen);
            b = dis(gen);
            if(!m[a].count(b)) break;
        }
        G[a].push_back({b, 0});
        m[a].insert(b);
    }
    return G;
}

Graph reverse(const Graph& G) {
    int n = G.size();
    Graph RG(n);
    for(int i = 0; i < n; i++) {
        for(Edge e : G[i]) {
            RG[e.dst].push_back({i, 0});
        }
    }
    return RG;
}

TEST(Tarjan, Large){
    int n = 1e6;
    int E = 1e6;
    Graph g = random(n, E);
    Graph rg = reverse(g);
    vector<int> ord;
    tarjan(g, ord);
}

TEST(Tarjan, LargeSCC){
    int n = 1e6;
    int E = 1e6;
    Graph g = random(n, E);
    Graph rg = reverse(g);
    vector<int> ord;
    scc(g, rg, ord);
}

TEST(Tarjan, OrderCheck){
    int n = 1e5;
    int E = 1e5;
    Graph g = random(n, E);
    Graph rg = reverse(g);
    vector<int> ord;
    
    tarjan(g, ord);
    REP(u, n) for(Edge e : g[u]) {
        ASSERT_TRUE(ord[u] <= ord[e.dst]) << "tarjan failed : " << ord[u] << " <= " << ord[e.dst] << endl;
    }

    scc(g, rg, ord);
    REP(u, n) for(Edge e : g[u]) {
        ASSERT_TRUE(ord[u] <= ord[e.dst]) << "scc failed : " << ord[u] << " <= " << ord[e.dst] << endl;
    }
}

TEST(Tarjan, SizeCheck) {
    int n = 1e5;
    int e = 1e5;
    Graph g = random(n, e);
    Graph rg = reverse(g);
    vector<int> ord1, ord2;
    int K1 = tarjan(g, ord1);
    int K2 = scc(g, rg, ord2);
    ASSERT_EQ(K1, K2);
    sort(ord1.begin(), ord1.end());
    sort(ord2.begin(), ord2.end());
    ASSERT_EQ(ord1, ord2);
}

TEST(Tarjan, ZOJ3795) {
    int n = 1e5;
    int E = 1e5;
    Graph g = random(n, E);
    Graph rg = reverse(g);
    vector<int> ord1, ord2;

    // SCC1
    int K1 = tarjan(g, ord1);
    vector<int> size1(K1);
    REP(u, n) size1[ ord1[u] ]++;
    vector<int> dp1(K1);
    REP(i, K1) dp1[i] = size1[i];
    REP(u, n) for(Edge e : g[u]) {
        int v = e.dst;
        dp1[ord1[v]] = max(dp1[ord1[v]], dp1[ord1[u]] + size1[ord1[v]]);
    }

    // SCC2
    int K2 = scc(g, rg, ord2);
    vector<int> size2(K2);
    REP(u, n) size2[ ord2[u] ]++;
    vector<int> dp2(K2);
    REP(i, K2) dp2[i] = size2[i];
    REP(u, n) for(Edge e : g[u]) {
        int v = e.dst;
        dp2[ord2[v]] = max(dp2[ord2[v]], dp2[ord2[u]] + size2[ord2[v]]);
    }

    // answer
    ASSERT_EQ(*max_element(dp2.begin(), dp2.end()), *max_element(dp1.begin(), dp1.end()));

    // size
    sort(size1.begin(), size1.end());
    sort(size2.begin(), size2.end());
    ASSERT_EQ(size1, size2);

    // dp
    sort(dp1.begin(), dp1.end());
    sort(dp2.begin(), dp2.end());
    ASSERT_EQ(dp1, dp2);
}
