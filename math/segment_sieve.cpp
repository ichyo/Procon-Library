#include "../common/common.h"

// [a, b)の整数に対して素数テーブルを作る．is_prime[i - a] = true <-> iが素数
vector<bool> segment_sieve(LL a, LL b){
    int q = int(sqrt(b) + 2);
    vector<bool> is_prime(b - a, true);
    vector<bool> is_prime_small(q, true);

    for(int i = 2; (LL)i * i < b; i++){
        if(is_prime_small[i]){
            for(int j = 2 * i; (LL)j * j < b; j += i)
                is_prime_small[j] = false;
            for(LL j = max(2LL, (a + i - 1) / i) * i; j < b; j += i)
                is_prime[j - a] = false;
        }
    }

    return is_prime;
}
