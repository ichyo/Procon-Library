
struct Rational{
    // p : 分子 q : 分母
    LL p, q;
    void normalize(){
        if(q < 0) {
            p *= -1;
            q *= -1;
        }
        LL d = __gcd(abs(p), q);
        if(d == 0){
            p = 0;
            q = 1;
        }else{
            p /= d;
            q /= d;
        }
    }
    Rational(LL p, LL q) : p(p), q(q) {
        normalize();
    }

};

Rational operator + (const Rational& a, const Rational& b){
    return Rational(a.p * b.q + b.p * a.q, a.q * b.q);
}

Rational operator - (const Rational& a, const Rational& b){
    return Rational(a.p * b.q - b.p * a.q, a.q * b.q);
}

Rational operator * (const Rational& a, const Rational& b){
    return Rational(a.p * b.p, a.q * b.q);
}

Rational operator / (const Rational& a, const Rational& b){
    return Rational(a.p * b.q, a.q * b.p);
}

bool operator == (const Rational& a, const Rational& b){
    return (a.p == b.p) && (a.q == b.q);
}

bool operator < (const Rational& a, const Rational& b){
    // overflowを避けるためにlong doubleを用いる
    return (long double) a.p * b.q < (long double) b.p * a.q;
}
