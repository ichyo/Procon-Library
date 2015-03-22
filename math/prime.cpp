#include "../common/common.h"
#include "./mod.cpp"

// 与えられた数が素数かどうかをO(logˆ3 n)で確率的に判定する.
// 以下の関数はn < 341,550,071,728,321について決定的である.
bool miller_rabin(LL n){
    if(n == 2) return true;
    if(n % 2 == 0 || n <= 1) return false;

    vector<LL> a = {2, 3, 5, 7, 11, 13, 17};

    LL d = n - 1, s = 0;
    while((d & 1) == 0){
        d >>= 1;
        s++;
    }

    for(int i = 0; i < a.size() && a[i] < n; i++){
        LL x = pow_mod(a[i], d, n);
        if(x == 1) continue;
        for(int r = 0; r < s; r++){
            if(x == n - 1) break;
            if(r + 1 == s) return false;
            x = mul_mod(x, x, n);
        }
    }

    return true;
}

