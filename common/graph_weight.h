struct Edge{
    int dst, cost;
};

typedef vector<Edge> Node;
typedef vector<Node> Graph;

void add_edge(Graph& G, int a, int b, int c) {
    G[a].push_back({b, c});
}
