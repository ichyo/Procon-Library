
struct Node{
    int val;
    double pri;
    int cnt;
    int sum;
    int min_v;
    Node* lch;
    Node* rch;

    Node(int v, double p) :
        val(v), pri(p), cnt(1), sum(v), min_v(v), lch(NULL), rch(NULL) {}
};

int count(Node* t) {
    return t ? t->cnt : 0;
}
int sum(Node* t) {
    return t ? t->sum : 0;
}
int min(Node* t) {
    return t ? t->min_v : INT_MAX;
}

Node* update(Node* t) {
    t->cnt = 1 + count(t->lch) + count(t->rch);
    t->sum = t->val + sum(t->lch) + sum(t->rch);
    t->min_v = min(t->val, min( min(t->lch), min(t->rch) ));
    return t;
}

Node* merge(Node* l, Node* r) {
    if(!l || !r) return l ? l : r;

    if(l->pri > r->pri) {
        l->rch = merge(l->rch, r);
        return update(l);
    } else {
        r->lch = merge(l, r->lch);
        return update(r);
    }
}

pair<Node*, Node*> split(Node* t, int k) { // [0, k) [k, n)
    if(!t) return pair<Node*, Node*>(NULL, NULL);

    int c = count(t->lch);
    if(k <= c) {
        pair<Node*, Node*> s = split(t->lch, k);
        t->lch = s.second;
        return make_pair(s.first, update(t));
    } else {
        pair<Node*, Node*> s = split(t->rch, k - (c + 1));
        t->rch = s.first;
        return make_pair(update(t), s.second);
    }
}

Node* insert(Node* t, int k, int v) {
    auto p = split(t, k);
    return merge(merge(p.first, new Node(v, rand())), p.second);
}

Node* erase(Node* t, int k) {
    auto p1 = split(t, k);
    auto p2 = split(p1.second, 1);
    return merge(p1.first, p2.second);
}

int minimum(Node *t, int l, int r) {
    if(!t) return INT_MAX;
    int c = count(t->lch);
    int n = count(t);
    // [0, c - 1] c [c + 1, n - 1]
    if(l <= 0 && n - 1 <= r) {
        return min(t);
    }
    int res = INT_MAX;
    if(!(c - 1 < l || r < 0)) {
        res = min(res, minimum(t->lch, l, r));
    }
    if(l <= c && c <= r) {
        res = min(res, t->val);
    }
    if(!(r < c + 1 || n - 1 < l)) {
        int nl = l - (c + 1);
        int nr = r - (c + 1);
        res = min(res, minimum(t->rch, nl, nr));
    }
    return res;
}

// --- for debug ---

Node* get(Node* t, int k) {
    int c = count(t->lch);
    if(k < c) {
        return get(t->lch, k);
    } else if(k > c) {
        return get(t->rch, k - (c + 1));
    } else {
        return t;
    }
}

void output(Node* t) {
    int n = count(t);
    REP(i, n) {
        cout << get(t, i)->val << " ";
    }
    cout << endl;
}
