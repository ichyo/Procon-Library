
struct Node{
    int value;
    map<char, Node*> next;
    Node() : value(0) {}
    ~Node(){ for(auto p : next) if(p.second) delete p.second; }
};

Node* find(Node* root, string s){
    Node* p = root;
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        if(!p->next[c]) p->next[c] = new Node();
        p = p->next[c];
    }
    return p;
}

