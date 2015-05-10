// Aho Corasick
// 複数のパターンのマッチングを，文字列の長さに線形な時間で行う．
//
// build(patterns)
// パターンマッチングオートマトンを構築する．
// 計算量: O(sum of |patterns_i|)
//
// next_node(p, c):
// オートマトンにおける，移動先を計算する．
// 引数は，現在のノードと，入力文字
//
// match(root, query):
// マッチするパターンとその位置をベクトルで返す．
// 引数はオートマトンのルートノードと検索文字列．
// 計算量は: O(|query|)
//
// 例:
// vector<string> patterns = {"aaa", "abc"};
//
// Node* root = build(patterns);
//
// vector<P> v = match(root, "aaaabc");
//
// assert(v == vector<P>({{2, 0}, {3, 0}, {5, 1}}));
// // s[0..2] == patterns[0]
// // s[1..3] == patterns[0]
// // s[2..5] == patterns[1]
//
// Verified: AOJ 2212

struct Node{
    map<char, Node*> next;
    Node* fail;
    vector<int> match;
    Node() : fail(NULL) {}
    ~Node(){ for(auto p : next) if(p.second) delete p.second; }
};

Node *build(vector<string> pattens){
    // 1. trie木 をつくる
    Node* root = new Node();
    root->fail = root;
    for(int i = 0; i < pattens.size(); i++){
        Node* p = root;
        for(auto c : pattens[i]){
            if(p->next[c] == 0) p->next[c] = new Node();
            p = p->next[c];
        }
        p->match.push_back(i);
    }

    // 2. failure link を作る
    queue<Node*> que;
    for(int i = 0; i < 128; i++){
        if(!root->next[i]){
            root->next[i] = root;
        }else{
            root->next[i]->fail = root;
            que.push(root->next[i]);
        }

    }
    while(!que.empty()){
        Node* p = que.front(); que.pop();
        for(auto a : next) {
            int i = a.first;
            Node* np = a.second;
            if(!np) continue;

            // add que
            que.push(np);

            // search failure link
            Node* f = p->fail;
            while(!f->next[i]) f = f->fail;
            np->fail = f->next[i];

            // update matching list
            np->match.insert(np->match.end(), np->fail->match.begin(), np->fail->match.end());
        }
    }
    return root;
}

// Trie木のノード p からの 文字 c に対応する移動先
Node* next_node(Node* p, char c) {
    while(!p->next[c]) p = p->fail;
    return p->next[c];
}

// クエリにマッチしたパターンについて 
// (last index, pattern id)のリストを返す
typedef pair<int, int> P;
vector<P> match(Node* root, string query){
    int n = query.size();
    vector<P> res;

    Node* p = root;
    REP(i, n) {
        int c = query[i];
        p = next_node(p, c);
        for(int k : p->match){
            res.push_back(P(i, k));
        }
    }

    return res;
}
