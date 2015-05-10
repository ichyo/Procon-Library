#include "../../common/common.h"

struct Node{
    int val;
    Node* child;
    Node* next;

    Node() : val(0), child(nullptr), next(nullptr) {}
    Node(int v) : val(v), child(nullptr), next(nullptr) {}
};

struct BinomialTree {
    Node* root;
    int rank;
    BinomialTree() : root(nullptr), rank(-1) {}
    BinomialTree(Node* p, int r) : root(p), rank(r) {}
    BinomialTree addSubTree(BinomialTree t);
    vector<BinomialTree> subTrees();
};

BinomialTree BinomialTree::addSubTree(BinomialTree t){
    t.root->next = root->child;
    root->child = t.root;
    rank++;
    return *this;
}

BinomialTree mergeTree(BinomialTree p, BinomialTree q) {
    if(!p.root) {
        return q;
    } else if(!q.root) {
        return p;
    } else if(p.root->val <= q.root->val) {
        return p.addSubTree(q);
    } else {
        return q.addSubTree(p);
    }
}

vector<BinomialTree> BinomialTree::subTrees() {
    vector<BinomialTree> res;
    int r = rank;
    for(Node* p = root->child; p; p = p->next) {
        res.push_back(BinomialTree(p, --r));
    }
    return res;
}

struct BinomialHeap {
    static const int MAX_T = 25; // the number of elements < 33554432
    BinomialTree trees[MAX_T];

    int top();
    BinomialHeap push(int x);
    BinomialHeap pop();
};

BinomialHeap mergeHeap(BinomialHeap p, BinomialHeap q) {
    BinomialHeap res;
    BinomialTree cur;
    BinomialTree next;
    for(int i = 0; i < BinomialHeap::MAX_T; i++) {
        if(p.trees[i].root && q.trees[i].root && next.root) {
            res.trees[i] = next;
            next = mergeTree(p.trees[i], q.trees[i]);
        } else {
            BinomialTree tree = mergeTree(p.trees[i], q.trees[i]);
            if(next.root) {
                tree = mergeTree(tree, next);
                next.root = nullptr;
            }
            if(tree.rank == i) {
                res.trees[tree.rank] = tree;
            } else if(tree.rank == i+1) {
                next = tree;
            } else {
                assert(tree.rank == -1);
            }
        }
    }
    return res;
}

int BinomialHeap::top() {
    int res = INT_MAX;
    for(int i = 0; i < MAX_T; i++) {
        if(trees[i].root) {
            res = min(res, trees[i].root->val);
        }
    }
    return res;
}

BinomialHeap BinomialHeap::push(int x) {
    BinomialHeap heap;
    heap.trees[0] = BinomialTree(new Node(x), 0);
    return mergeHeap(*this, heap);
}

BinomialHeap BinomialHeap::pop() {
    int minidx = -1;
    for(int i = 0; i < MAX_T; i++) {
        if(trees[i].root &&
                (minidx == -1 || trees[minidx].root->val > trees[i].root->val)) {
            minidx = i;
        }
    }

    vector<BinomialTree> subtrees = trees[minidx].subTrees();

    BinomialHeap subheap;
    for(auto tree : subtrees) {
        subheap.trees[tree.rank] = tree;
    }

    BinomialHeap remheap = *this;
    // delete remheap.trees[minidx].root; // OMG
    remheap.trees[minidx] = BinomialTree();

    return mergeHeap(subheap, remheap);
}

int main() {
    const int N = 1000;

    vector<int> v(N);
    REP(i, N) v[i] = rand();

    vector<int> w = v;
    sort(w.begin(), w.end());

    BinomialHeap heap;

    REP(i, N){
        heap = heap.push(v[i]);
    }

    vector<int> a;
    REP(i, N){
        a.push_back(heap.top());
        cout << a[i] << " " << w[i] << endl;
        assert(a[i] == w[i]);
        heap = heap.pop();
        heap.print();
    }
    assert(a == w);
    return 0;
}
