
struct SAT2{
    int n, V;
    Graph G, RG;
    vector<int> truth;

    SAT2(int n) : n(n), V(2 * n), G(V) {}

    // p は 真 (<=> "(not p) ならば p")
    void set_t(int p){
        imply(inv(p), p);
    }

    // p または q (<=> "(not a) ならば b" かつ "(not b) ならば a")
    void set_or(int p, int q) {
        imply(inv(p), q);
        imply(inv(q), p);
    }

    // p ならば q
    void imply(int p, int q){
        add_edge(G, p, q);
        add_edge(RG, q, p);
    }


    // 充足可能か判定(各変数の真偽値が`truth`に入る)
    bool satisfy(){
        vector<int> comp;
        scc(G, RG, comp);
        truth.assign(n, false);
        for(int i = 0; i < n; i++){
            if(comp[i] == comp[i + n]) return false;
            if(comp[i] > comp[i + n]) truth[i] = true;
        }
        return true;
    }

    // not p
    int inv(int p){
        return (p + n) % V;
    }
};
