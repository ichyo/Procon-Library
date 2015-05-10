
// UnionFind 
struct UnionFind {
    vector<int> data;
    UnionFind(int N) : data(N, -1) { }
    // xとyを併合する
    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if (x != y) {
            if (data[x] > data[y]) swap(x, y);
            data[x] += data[y]; data[y] = x;
        }
        return x != y;
    }
    // xとyが同じ集合にあるか判定する
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    // xを含む集合の要素数を求める
    int size(int x) {
        return -data[root(x)];
    }
    int root(int x) {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
};

// UnionFind (重み付き)
struct UnionFindW{
    vector<pair<int, int>> uf; // (parent, offset from parent)
    UnionFindW(int N) {
        for(int i = 0; i < N; i++){
            uf.push_back(make_pair(i, 0));
        }
    }

    // return (root, offset from root)
    pair<int, int> root(int a){
        if(uf[a].first != a){
            pair<int, int> p = root(uf[a].first);
            uf[a] = make_pair(p.first, p.second + uf[a].second);
        }
        return uf[a];
    }

    // (a, b, offset of [b] - offset of [a])
    bool unite(int a, int b, int d){
        pair<int, int> pa = root(a), pb = root(b);
        int ra = pa.first, rb = pb.first;
        if(ra != rb) {
            uf[ra] = make_pair(rb, pb.second - pa.second + d);
        }
        return ra != rb;
    }

    // 同じ集合に含まれるかどうか
    bool same(int x, int y) {
        return root(x).first == root(y).first;
    }
};
