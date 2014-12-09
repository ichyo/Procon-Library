// 点集合 ps をすべて含む円のうち，半径最小の円を求める
// verify: aoj 2423
C smallest_circle(const vector<P>& ps) {
    const double init = 1.0;
    const double rate = 0.99; // 1e-9 ~ (0.99^2000)
    if(ps.empty()) return {{0, 0}, 0};
    double T = init;
    P cur;
    while(T > EPS) {
        P to = ps.front();
        for(P p : ps) if(abs(to - cur) < abs(p - cur)) {
            to = p;
        }
        cur += (to - cur) * T;
        T *= rate;
    }
    double r = 0;
    for(P p : ps) {
        r = max(r, abs(p - cur));
    }
    return {cur, r};
}
