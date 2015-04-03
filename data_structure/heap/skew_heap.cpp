#include "../../common/common.h"

template<typename T>
struct Heap {
    T val;
    Heap *l, *r;
    Heap(T x=T()) : val(x), l(nullptr), r(nullptr) {}
};

template<typename T>
Heap<T>* meld(Heap<T>* a, Heap<T>* b) {
    if(!a) return b;
    if(!b) return a;
    if(b->val < a->val) swap(a, b);
    a->r = meld(a->r, b);
    swap(a->l, a->r);
    return a;
}

template<typename T>
class SkewHeap {
    int s;
    Heap<T>* h;
public:
    SkewHeap() : s(0), h(nullptr) {}
    bool empty() const {
        return s == 0;
    }
    int size() const {
        return s;
    }
    const T& top() const {
        return h->val;
    }
    void push(const T& x) {
        s++;
        h = meld(h, new Heap<T>(x));
    }
    void pop() {
        s--;
        Heap<T>* nh = meld(h->l, h->r);
        delete h;
        h = nh;
    }
};

