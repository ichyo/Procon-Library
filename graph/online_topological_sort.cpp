// オンライントポロジカルソート
// 概要:
// オンライン版のトポロジカルソート．
// 辺が加えられるたびに頂点のトポロジカル順序を変更する．
//
// 注意点:
// - 閉路ができるような場合(DAGにならない場合)は考慮していない
//
// 計算量:
// O((V + E) * Q)
// Qはクエリ数
// 
// 使い方:
// /* 頂点の個数を指定 */
// OnlineTopologicalSort solver(n);
// /* 辺を追加 */
// solver.add_edge(1, 0);
// solver.add_edge(2, 1);
// /* 頂点uのトポロジカル順序を出力 */
// cout <<< solver.get_order(u) << endl;
// /* トポロジカル順序がiの頂点を出力 */
// for(int i = 0; i < n; i++){
//     cout << solver.get_node(i) << endl;
// }
//
//
// Verify:
// IOPC2014 D Problem
//
class OnlineTopologicalSort{
    Graph G; // グラフ
    vector<int> order; // 頂点uの順位
    vector<int> order_inv; // 順位iの頂点
    vector<bool> color; // dfsで辿れるノードを保存する
    int lb, ub;

    // 頂点xの順位をiに定める
    inline void allocate(int x, int i){
        order[x] = i;
        order_inv[i] = x;
    }

    // 順位がub以下の頂点を経由して辿れる頂点に色を塗る
    void dfs(int v){
        color[v] = true;
        for(int next : G[v]){
            if(order[next] < ub && !color[next]){
                dfs(next);
            }
        }
    }

    // 色が塗られた頂点を右側に寄せる
    void shift_node(){
        vector<int> shift;
        for(int i = lb; i <= ub; i++){
            int w = order_inv[i];
            if(color[w]){
                color[w] = false;
                shift.push_back(w);
            }else{
                allocate(w, i - shift.size());
            }
        }
        for(int i = 0; i < shift.size(); i++){
            allocate(shift[i], ub - shift.size() + i + 1);
        }
    }

    public: 

    // 頂点数N
    OnlineTopologicalSort(int N) : 
        G(N), order(N), order_inv(N), color(N)
    {
        for(int i = 0; i < N; i++){
            allocate(i, i);
        }
    }

    // 有向辺 a -> b を加える
    void add_edge(int a, int b){
        G[a].push_back(b);
        lb = order[b];
        ub = order[a];
        if(lb < ub){ // bがaよりも左側にあるとき
            dfs(b); // bから辿れる頂点を列挙する
            shift_node(); // bから辿れる頂点を右側に，残りの頂点を左側に，
                          // 順序を保ったまま移動する
        }
    }

    // 頂点uのトポロジカル順序 (0-based index)
    int get_order(int u) const {
        return order[u];
    }

    // トポロジカル順序がnth番目の頂点 (0-based index)
    int get_node(int nth) const {
        return order_inv[nth];
    }

};
