
// [2, N] の範囲の素数を列挙する。
vector<int> all_primes(int N) {
    vector<bool> b(N+1, true);
    vector<int> res;
    for(int i = 2; i <= N; i++) {
        if(!b[i]) continue;
        res.push_back(i);
        if((LL)i*i > N) continue;
        for(int j=i*i; j <= N; j+=i) {
            b[j] = false;
        }
    }
    return res;
}

// 整数 N の約数を列挙する O(sqrt(N))
vector<LL> divisor(LL N) {
    vector<LL> res;
    for(LL i = 1; i*i <= N; i++) {
        if(N % i != 0) continue;
        res.push_back(i);
        if(i != N/i) res.push_back(N/i);
    }
    sort(res.begin(), res.end());
    return res;
}

// 素因数分解をする。例: 12 -> {2:2, 3:1} : O(sqrt(N))
map<LL, int> factorize(LL N, const vector<int>& primes) {
    // assert(primes is superset of all_primes(sqrt(N)))
    // assert(primes is sorted)
    map<LL, int> res;
    for(auto p : primes) {
        if((LL)p*p > N) break;
        if(N % p != 0) continue;
        int c = 0;
        while(N % p == 0) {
            c++;
            N /= p;
        }
        res[p] = c;
    }
    if(N > 1) res[N] = 1;
    return res;
}


// 与えられた数が素数かどうかをO(log^3 n)で確率的に判定する
// 以下の関数はn < 341,550,071,728,321について正しい
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

// [a, b)の整数に対して素数テーブルを作る．
// is_prime[i-a]==true <-> iが素数
vector<bool> segment_sieve(LL a, LL b){
    assert(a < b);
    assert(a >= 2);
    int q = int(sqrt(b) + 2);
    vector<bool> is_prime(b-a, true);
    vector<bool> is_prime_small(q, true);

    for(int i = 2; (LL)i*i < b; i++){
        if(!is_prime_small[i]) continue;
        for(int j = 2*i; (LL)j*j < b; j+=i) {
            is_prime_small[j] = false;
        }
        for(LL j = max(2LL, (a+i-1)/i)*i; j < b; j+=i) {
            is_prime[j-a] = false;
        }
    }

    return is_prime;
}
