// 入力
// ss : 線分のリスト
//
// 出力
// ps : グラフの頂点番号に対応する点が入る
// 返り値 : 上の説明のグラフ
//
// Verified
// AOJ 2113
struct Edge{ int src, dst; double cost; };
typedef vector<Edge> Node;
typedef vector<Node> Graph;
Graph segment_arrangement(const vector<L> &ss, vector<P> &ps) {
    for (int i = 0; i < ss.size(); i++) {
        ps.push_back( ss[i][0] );
        ps.push_back( ss[i][1] );
        for (int j = i+1; j < ss.size(); j++){
            if (iSS(ss[i], ss[j])) {
                ps.push_back( pLL(ss[i], ss[j])[0] );
            }
        }
    }
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());

    Graph g(ps.size());
    for (int i = 0; i < ss.size(); i++) {
        vector<int> on;
        for (int j = 0; j < ps.size(); j++){
            if (iSP(ss[i], ps[j])){
                on.push_back(j);
            }
        }
        for (int j = 0; j + 1 < on.size(); j++) {
            int a = on[j], b = on[j + 1];
            g[a].push_back( {a, b, abs(ps[a]-ps[b])} );
            g[b].push_back( {b, a, abs(ps[a]-ps[b])} );
        }
    }
    return g;
}

// 線分併合
//
// 線分のリストからオーバーラップするものたちをまとめ,新しい線分のリストを作る.
// 元々の線分のリストにおける順番は破壊される．
//
// Verified
// AOJ 2113
void merge_segments(vector<L>& segs) {
    auto merge_if_able = [](L& s, L t){
        if (abs(cross(s[1]-s[0], t[1]-t[0])) > EPS) return false;
        if (ccw(s[0], t[0], s[1]) == +1 ||
                ccw(s[0], t[0], s[1]) == -1) return false; // not on the same line
        if (ccw(s[0], s[1], t[0]) == -2 ||
                ccw(t[0], t[1], s[0]) == -2) return false; // separated
        s = { min(s[0], t[0]), max(s[1], t[1]) };
        return true;
    };
    for (int i = 0; i < segs.size(); ++i)
        if (segs[i][1] < segs[i][0])
            swap(segs[i][1], segs[i][0]);
    for (int i = 0; i < segs.size(); ++i)
        for (int j = i+1; j < segs.size(); ++j)
            if (merge_if_able(segs[i], segs[j]))
                segs[j--] = segs.back(), segs.pop_back();
}
