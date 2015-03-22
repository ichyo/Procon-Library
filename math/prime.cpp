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

// [a, b)の整数に対して素数テーブルを作る．is_prime[i-a]==true <-> iが素数
vector<bool> segment_sieve(LL a, LL b){
    assert(a < b);
    assert(a >= 2);
    int q = int(sqrt(b) + 2);
    vector<bool> is_prime(b - a, true);
    vector<bool> is_prime_small(q, true);

    for(int i = 2; (LL)i*i < b; i++){
        if(is_prime_small[i]){
            for(int j = 2*i; (LL)j*j < b; j+=i)
                is_prime_small[j] = false;
            for(LL j = max(2LL, (a+i-1)/i)*i; j < b; j+=i)
                is_prime[j - a] = false;
        }
    }

    return is_prime;
}
