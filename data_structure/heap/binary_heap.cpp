#include "../../common/common.h"

template<typename T, typename Compare = less<T>>
class BinaryHeap{ // minHeap
    vector<T> v;
    Compare comp;
public:
    bool empty() const {
        return v.empty();
    }
    int size() const {
        return v.size();
    }
    T top() const {
        return v.front();
    }
    void push(T x) {
        int k = v.size();
        v.push_back(x);
        while(k > 0) {
            int p = (k-1) / 2; // parent index
            if(comp(v[p], v[k])) break;
            swap(v[p], v[k]);
            k = p;
        }
    }
    void pop() {
        swap(v.front(), v.back());
        v.pop_back();

        int k = 0;
        while(true) {
            int l = 2*k + 1;
            int r = 2*k + 2;
            int smallest = k;
            if(l < v.size() && comp(v[l], v[smallest])) smallest = l;
            if(r < v.size() && comp(v[r], v[smallest])) smallest = r;
            if(smallest == k) break;
            swap(v[k], v[smallest]);
            k = smallest;
        }
    }
};
