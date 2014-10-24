typedef vector<P> L;
P vec(L l){return l[1] - l[0];}

// 注意: 端点で交わったり直線が重なったりする場合も交差していると判定する

// 二直線の平行判定
// verify : AOJ0021
bool paralell(L l, L m){return sign(cross(vec(l), vec(m))) == 0;}

// 二直線の同一判定
bool equalLL(L l, L m){return paralell(l, m) && sign(cross(vec(l), m[0] - l[0])) == 0;}

// 直線と点の交差判定
// 直線lとl[0]からpへの直線が平行
bool iLP(L l, P p) {return sign(cross(vec(l), p - l[0])) == 0;}

// 線分と点の交差判定(端点の処理に注意)(端点は含むけれども誤差に注意)
// verify : AOJ1279, AOJ2506
bool iSP(L s, P p) {return ccw(s[0], s[1], p) == 0;}

// 直線と線分の交差判定(線分が重なっている時に注意)
// 直線lについて、線分sの端点が異なる側にある
bool iLS(L l, L s) {return sign(cross(vec(l), s[0] - l[0]) * cross(vec(l), s[1] - l[0])) <= 0;}

// 二つの線分の交差判定(線分が重なっている時や端点の処理に注意)
bool iSS(L s, L t) {
    auto ok = [](L a, L b){return ccw(a[0],a[1],b[0]) * ccw(a[0],a[1],b[1]) <= 0;};
    return ok(s,t) && ok(t,s);
}


// 点pから直線lに対する射影
P proj(L l, P p){
    double t = dot(p - l[0], vec(l)) / norm(vec(l));
    return l[0] + t * vec(l);
}

// 点pの直線lに関する反射
P refl(L l, P p){return 2.0 * proj(l, p) - p;}

// 直線と点の距離
// Verified: AOJ 2201
double dLP(L l, P p){return abs(cross(vec(l), p - l[0])) / abs(vec(l));}

// 線分と点の距離
double dSP(L s, P p){
    if(sign(dot(vec(s), p - s[0])) <= 0) return abs(p - s[0]);
    if(sign(dot(-vec(s), p - s[1])) <= 0) return abs(p - s[1]);
    return dLP(s, p);
}

// 直線と直線の距離
// 平行でないときは0, 平行のときは垂線の長さ
double dLL(L l, L m){ return paralell(l, m) ? dLP(l, m[0]) : 0; }

// 直線と線分の距離
double dLS(L l, L s){ return iLS(l,s) ? 0.0 : min(dLP(l, s[0]), dLP(l, s[1])); }

// 線分と線分の距離
// Verified: AOJ 1157
double dSS(L s, L t){return iSS(s,t) ? 0.0 : min({dSP(s, t[0]), dSP(s, t[1]), dSP(t, s[0]), dSP(t, s[1])});}

// 直線と直線の交点
// Verified: AOJ2579
// size()によって場合分け
// *4 : 直線が重なる  *1 : 交点が1つ存在 *0 : 直線が交差しない
vector<P> pLL(L l, L m){
    double A = cross(vec(l), vec(m));
    double B = cross(vec(l), l[1] - m[0]);
    if(sign(A) == 0 && sign(B) == 0) return {l[0], l[1], m[0], m[1]}; // 二直線が重なっている
    if(sign(A) == 0) return{}; // 直線が交わらない
    return {m[0] + vec(m) * B / A};
}

// 線分と線分の交点
// TODO: {(0, 0), (1, 0)} {(1, 0), (2, 0)}を投げたときに空集合が返ってきてしまう．(←直った?)
vector<P> pSS(L l, L m){
    vector<P> res;
    auto find = [&](P p){ 
        for(P r : res)
            if(sign(abs(r - p)) == 0)
                return true;
        return false;
    };
    for(P p : pLL(l, m)){
        // 片方が直線の場合は適宜変えること
        if(iSP(l,p) && iSP(m,p) && !find(p)){
            res.push_back(p);
        }
    }
    return res;
}
