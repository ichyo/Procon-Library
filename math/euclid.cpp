
LL gcd(LL a, LL b){
    return b > 0 ? gcd(b, a % b) : a;
}

LL lcm(LL a, LL b){
    return a / gcd(a, b) * b;
}

// a x + b y = gcd(a, b) なる x, y を求める
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
