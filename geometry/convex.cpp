// 凸包
Pol convex_hull(vector<P> ps) {
    int n = ps.size(), k = 0;
    sort(ps.begin(), ps.end());

    vector<P> ch(2*n);
    for (int i = 0; i < n; ch[k++] = ps[i++]){ // lower-hull
        while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
    }
    for (int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--]){ // upper-hull
        while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
    }
    ch.resize(k-1);
    return ch;
}

bool is_convex(const Pol& A){
    int n = A.size();
    for(int i = 0; i < n; i++){
        if(ccw(A[i], A[(i + 1) % n], A[(i + 2) % n]) > 0) return false;
    }
    return true;
}

// 凸多角形の直線による切断。直線の左側だけ残す
// verify : aoj1283
Pol convex_cut(const Pol& A, L l){
    int n = A.size();
    Pol B;
    for(int i = 0; i < n; i++){
        P a = A[i], b = A[(i + 1) % n];
        if(ccw(l[0], l[1], a) != -1) B.push_back(a); //Aが直線lの右側でない
        if(ccw(l[0], l[1], a) * ccw(l[0], l[1], b) < 0)
            B.push_back(pLL(l, {a, b})[0]);
    }
    return B;
}
// 垂直二等分線
// verify: maximamcup2013 D
L bisector(P a, P b){
    P mid = (a + b) / 2.0;
    P vec = (mid - a) * P(0.0, 1.0);
    return {mid, mid + vec};
}
// 点集合psのうちs番目のボロノイ領域
// verify: maximamcup2013 D
Pol voronoi_cell(Pol A, const vector<P>& ps, int s){
    for(int i = 0; i < ps.size(); i++){
        if(i != s) A = convex_cut(A, bisector(ps[s], ps[i]));
    }
    return A;
}
