#include "../common/common.h"
// 剰余を自動で行うためのクラス
static const unsigned MODVAL = 1000000007;
struct mint {
    unsigned val;
    mint():val(0){}
    mint(int      x):val(x%MODVAL) {}
    mint(unsigned x):val(x%MODVAL) {}
    mint(LL       x):val(x%MODVAL) {}
};
mint& operator+=(mint& x, mint y) { return x = x.val+y.val; }
mint& operator-=(mint& x, mint y) { return x = x.val-y.val+MODVAL; }
mint& operator*=(mint& x, mint y) { return x = LL(x.val)*y.val; }
mint operator+(mint x, mint y) { return x+=y; }
mint operator-(mint x, mint y) { return x-=y; }
mint operator*(mint x, mint y) { return x*=y; }
