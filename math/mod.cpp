
LL extgcd(LL a, LL b, LL& x, LL& y){
    LL d = a;
    if(b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }else{
        x = 1; y = 0;
    }
    return d;
}

// mod * mod が long long に収まらない場合，
// 足し算でオーバーフローを避けてO(log b)で計算する
// mod * mod が long long に収まるときはreturn a * b % mod;に書き換える
LL mul_mod(LL a, LL b, LL mod){
    if(b == 0) return 0;
    LL res = mul_mod((a + a) % mod, b / 2, mod);
    if(b & 1) res = (res + a) % mod;
    return res;
}

// aのb乗をmodで割った余りをO(log b)で計算する
LL pow_mod(LL a, LL b, LL mod){
    if(b == 0) return 1;
    LL res = pow_mod(mul_mod(a, a, mod), b / 2, mod);
    if(b & 1) res = mul_mod(res, a, mod);
    return res;
}

// a * b % mod == 1 をみたすbを計算する．計算量はO(log mod)
// modが素数のときは b = a ^ (mod - 2)でも計算できる
LL inv_mod(LL a, LL mod){
    LL x, y;
    extgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

// 素数pを法とする，1..nの逆元のリストを求める． 計算量はO(n)
vector<LL> inverse_list(int n, int p){
    vector<LL> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i){
        inv[i] = inv[p % i] * (p - p / i) % p;
    }
    return inv;
}
