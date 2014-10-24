typedef vector<P> Pol; // 反時計回りを仮定

// 点が多角形のどこにあるのか判定する
// verify : AOJ0012
int contains(const Pol& A, P p){
    // 点pから半直線をひき、辺と交差する回数を数える
    int in = 0;
    int n = A.size();
    for(int i = 0; i < n; i++){
        P a = A[i] - p;
        P b = A[(i + 1) % n] - p;
        if(a.imag() > b.imag()) swap(a, b);
        // aからbの直線がy=0と交わり、その交点は原点の右側である
        in ^= a.imag() <= 0 && 0 < b.imag() && cross(a, b) < 0;

        if(sign(cross(a, b)) == 0 && sign(dot(a, b)) <= 0) return ON;
    }
    return in ? IN : OUT;
}

// 多角形の面積
// verify : AOJ0079 AOJ1100
double area(const Pol& A) {
    double res = 0;
    int n = A.size();
    for(int i = 0; i < n; i++){
        res += cross(A[i], A[(i + 1) % n]);
    }
    return abs(res) / 2.0;
}
