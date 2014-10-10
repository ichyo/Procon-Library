#include "../common/common.h"

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
        for(int i = 0; i < 128; i++) if(p->next[i]) {
            Node* np = p->next[i];

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

// クエリにマッチしたパターンについて 
// (last index, pattern id)のリストを返す
typedef pair<int, int> P;
vector<P> match(Node* root, string query){
    vector<P> res;
    Node* p = root;
    for(int i = 0; i < query.size(); i++){
        int c = query[i];
        while(!p->next[c]) p = p->fail; 
        p = p->next[c];
        for(auto k : p->match){
            res.push_back(P(i, k));
        }
    }
    return res;
}

