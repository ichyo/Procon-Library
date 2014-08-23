#include "shortest_path.cpp"
#include "../gtest/gtest.h"

Graph random(int n, int e, int d) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n-1);
    std::uniform_int_distribution<> disw(0, d-1);
    vector<set<int>> m(n);
    Graph G(n);
    for(int i = 0; i < e; i++) {
        int a, b, c;
        while(true){
            a = dis(gen);
            b = dis(gen);
            c = disw(gen);
            if(!m[a].count(b)) break;
        }
        G[a].push_back({b, c});
        m[a].insert(b);
    }
    return G;
}
Graph random_negative(int n, int e, int d) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n-1);
    std::uniform_int_distribution<> disw(-d + 1, d - 1);
    vector<set<int>> m(n);
    Graph G(n);
    for(int i = 0; i < e; i++) {
        int a, b, c;
        while(true){
            a = dis(gen);
            b = dis(gen);
            c = disw(gen);
            if(!m[a].count(b)) break;
        }
        G[a].push_back({b, c});
        m[a].insert(b);
    }
    return G;
}

TEST(BellmanFord, Large){
    int N = 1e4;
    int E = 1e4;
    int D = 1e4;
    Graph g = random_negative(N, E, D);
    bellmanford(g, 0);
}

TEST(SPFA, Large){
    int N = 1e4;
    int E = 1e4;
    int D = 1e4;
    Graph g = random_negative(N, E, D);
    SPFA(g, 0);
}

TEST(Dijkstra, Large){
    int N = 1e6;
    int E = 1e6;
    int D = 1e3;
    Graph g = random(N, E, D);
    dijkstra(g, 0);
}

TEST(All, ResultEqual) {
    int N = 1e4;
    int E = 1e4;
    int D = 1e4;
    int s = 123;
    Graph g = random(N, E, D);
    vector<int> d1 = bellmanford(g, s);
    vector<int> d2 = SPFA(g, s);
    vector<int> d3 = dijkstra(g, s);
    ASSERT_EQ(d1, d2);
    ASSERT_EQ(d2, d3);
}

TEST(NegativeAll, ResultEqual) {
    int N = 1e4;
    int E = 1e4;
    int D = 1e4;
    int s = 123;
    Graph g = random_negative(N, E, D);
    vector<int> d1 = bellmanford(g, s);
    vector<int> d2 = SPFA(g, s);
    ASSERT_EQ(d1, d2);
}
