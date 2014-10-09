typedef vector<int> Node;
typedef vector<Node> Graph;

void add_edge(Graph& G, int a, int b) {
    G[a].push_back(b);
}
