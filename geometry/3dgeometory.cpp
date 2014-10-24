struct P{
    double x, y, z;
    P() : x(0), y(0), z(0) {}
    P(double x, double y, double z) : 
        x(x), y(y), z(z) {}
};

P operator + (P a, P b){ return P(a.x + b.x, a.y + b.y, a.z + b.z); }
P operator - (P a, P b){ return P(a.x - b.x, a.y - b.y, a.z - b.z); }
P operator * (double t, P a){ return P(t * a.x, t * a.y, t * a.z); }

double dot(P a, P b){ return a.x * b.x + a.y * b.y + a.z * b.z; }
double abs(P a){ return sqrt(dot(a, a)); }
P cross(P a, P b){
    return P(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
            );
}

// 点aと点bを通る直線と，点cの距離
double distanceLP(P a, P b, P c){
    b = b - a; c = c - a; 
    double t = dot(b, c) / dot(b, b);
    return abs(c - b * t);
}

// a, bを通る直線と，c, dを通る直線の距離
double distanceLL(P a, P b, P c, P d){
    P v = cross(b - a, d - c); // 法線ベクトル
    P p = c - a;
    if(abs(v) < EPS) return distanceLP(a, b, c);
    double dst = abs(dot(v, p)) / abs(v);
    return dst;
}
