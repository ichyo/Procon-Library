#include "../common/common.h"
// 下側エンベロープ
// 複数の直線が与えられたときに，あるx座標での一番下側のy座標を効率的に計算する．
// この実装では，追加する直線の傾きが単調に減少することを仮定している．
// この仮定を外すときは，２分探索木などが必要となる．
//
// 直線の個数をn, クエリの回数をm としたとき，計算量はO(n + m)．
struct LowerEnvelope{
    int s, t;
    vector<LL> deq_a;
    vector<LL> deq_b;
    // f_i(x) = deq_a[i] * x + deq_b[i]
    // f2が最小値を取る可能性があるか判定
    inline bool check(LL a1, LL b1, LL a2, LL b2, LL a3, LL b3) const {
        return (a2 - a1) * (b3 - b2) >= (b2 - b1) * (a3 - a2);
    }
    LowerEnvelope(int n) :
        s(0), t(0), deq_a(n), deq_b(n) {}
    // 直線 ax + b を追加する． 前回追加した直線より傾きが小さい必要がある．
    void push(LL a, LL b){
        while(s + 1 < t && check(deq_a[t - 2], deq_b[t - 2], deq_a[t - 1], deq_b[t - 1], a, b)) t--;
        deq_a[t] = a;
        deq_b[t++] = b;
    }
    // f_i(x) のうち最小のものを返す． 前回のクエリよりもxが大きい必要がある．
    LL minimum(LL x){
        assert(s < t);
        while(s + 1 < t && deq_a[s] * x + deq_b[s] >= deq_a[s + 1] * x + deq_b[s + 1]) s++;
        return deq_a[s] * x + deq_b[s];
    }
};
