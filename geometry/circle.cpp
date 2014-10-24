struct C{P p;double r;};

// 円と点の内外判定
// Verified: AOJ2181, AOJ2579
int contains(C c, P p){
    double d = abs(c.p - p);
    if(sign(d - c.r) > 0) return OUT;
    if(sign(d - c.r) == 0) return ON;
    return IN;
}

// 円と線分の交差判定(境界を含む)
// 接するときに注意!!
// Verified: AOJ0129, AOJ2506, AOJ2579
bool iCS(C c, L l){
    int c1 = contains(c, l[0]);
    int c2 = contains(c, l[1]);
    if(c1 > c2) swap(c1, c2);

    // (OUT, OUT) (OUT, ON) (OUT, IN) (ON, ON) (ON, IN) (IN, IN) の6通り
    if(c1 == OUT && c2 == IN) return true;
    if(c1 == IN  && c2 == IN) return false;
    if(c1 == ON) return true; // (接するとき) 
    double d = dSP(l, c.p);
    if(sign(d - c.r) < 0) return true;
    if(sign(d - c.r) == 0) return true; // (接するとき)
    if(sign(d - c.r) > 0) return false;
    assert(false);
}

// 二つの円の交差判定(接する時を含む)
// verified: AOJ 2181
bool iCC(C c, C d){
    // 円の中心同士の距離が、半径の和以下であり、半径の差以上である
    double e = abs(d.p - c.p);
    return sign(e - (c.r + d.r)) <= 0 && sign(e - abs(c.r - d.r)) >= 0;
}

// 円cに対して円dがどの位置にあるか(IN:内側, ON: 交差, OUT: それ以外)
// Verified: AOJ 2181
int contains(C c, C d) {
    double e = abs(c.p - d.p);
    if(sign(c.r - d.r) > 0 && sign(c.r - (d.r + e)) > 0) return IN;
    if(iCC(c, d)) return ON;
    return OUT;
}

// 円と直線の交点
// verify : AOJ2045
vector<P> pCL(C c, L l) {
    vector<P> res;
    P center = proj(l, c.p);
    double d = abs(center - c.p);
    double tt = c.r * c.r - d * d;
    if(tt < 0 && tt > -EPS) tt = 0;
    if(tt < 0) return res;
    double t = sqrt(tt);
    P vect = vec(l);
    vect /= abs(vect);
    res.push_back(center - vect * t);
    if (t > EPS) {
        res.push_back(center + vect * t);
    }
    return res;
}

// 円と線分の交点
vector<P> pCS(C c, L s) {
    vector<P> ret;
    vector<P> nret = pCL(c, s);
    for (int i = 0; i < nret.size(); i++) {
        if (iSP(s, nret[i])) ret.push_back(nret[i]);
    }
    return ret;
}

// 円と円の交点
// verify : AOJ1190
vector<P> pCC(C a, C b) {
    vector<P> res;
 
    double d = abs(b.p - a.p);
    double l1 = abs(a.r - b.r);
    double l2 = a.r + b.r; 
 
    if(sign(d) == 0 && sign(l1) == 0) assert(false); // 円が等しい
    if(sign(d - l1) < 0 || sign(d - l2) > 0) return res; // 交わらない
 
    double th1 = arg(b.p - a.p);
 
    if(sign(d - l1) == 0 || sign(d - l2) == 0) { // 一点で交わる
        res.push_back(a.p + polar(a.r, th1));
    } else { // 二点で交わる
        double th2 = acos( (a.r * a.r - b.r * b.r + d * d) / (2 * a.r * d) );
        res.push_back(a.p + polar(a.r, th1 - th2));
        res.push_back(a.p + polar(a.r, th1 + th2));
    }
 
    return res;
}

// 2点を通る半径rの円の中心
// verify : AOJ1132
vector<P> touching_circle2(P a, P b, double r){
    vector<P> res;

    double d = abs(b - a);
    if(d > 2 * r) return res;

    P mid = 0.5 * (a + b);
    P dir = polar(sqrt(r * r - d * d / 4), arg(b - a) + M_PI / 2);
    res.push_back(mid + dir);
    res.push_back(mid - dir);
    return res;
}

// 3点を通る円
C touching_circle3(P a, P b, P c){
    // ２つの垂直二等分線の交点が円の中心
    P mid_ab = (a + b) / 2.0;
    L bis_ab = {mid_ab, (mid_ab - a) * P(0.0, 1.0)};
    P mid_bc = (b + c) / 2.0;
    L bis_bc = {mid_bc, (mid_bc - b) * P(0.0, 1.0)};

    assert(!paralell(bis_ab, bis_bc)); 

    P center = pLL(bis_ab, bis_bc)[0];
    return {center, abs(a - center)};
}

// 円と円の共通部分の面積を求める．
// ref: nya3j
double cc_area(C c1, C c2) {
    double d = abs(c1.p - c2.p);
    if (c1.r + c2.r < d + EPS) {
        return 0.0;
    } else if (d < abs(c1.r - c2.r) + EPS) {
        double r = min(c1.r, c2.r); // 元は c1.r >? c2.r だった．
        return r * r * M_PI;
    } else {
        double rc = (d*d + c1.r*c1.r - c2.r*c2.r) / (2*d);
        double theta = acos(rc / c1.r);
        double phi = acos((d - rc) / c2.r);
        return c1.r*c1.r*theta + c2.r*c2.r*phi - d*c1.r*sin(theta);
    }
}

