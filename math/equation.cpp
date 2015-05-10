// 2次方程式 ax^2 + bx + c = 0の解 (重解を一つにまとめる)
vector<double> quadratic(double a, double b, double c){
    if(abs(a) < EPS){
        // bx + c = 0
        if(abs(b) < EPS){
            // c = 0 のとき任意のxが解．c != 0 のとき解なし．
            return vector<double>();
        }
        return vector<double>(1, -c / b);
    }
    double D = b*b - 4*a*c;
    if(D < 0) return vector<double>();
    if(D == 0) return vector<double>(1, -b/(2.0 * a));

    // |b| >> |ac|の時の桁落ちを避けるために
    // x_1 = (-b-sign(b)*sqrt(D))/(2*a), x_2 = c / (a*x_1)を利用する
    vector<double> res;
    int sign = (b >= 0) ? 1 : -1;
    double x1 = (-b - sign * sqrt(D))/(2.0 * a);
    double x2 = c / (a * x1);
    res.push_back(x1);
    res.push_back(x2);
    return res;
}


//3次方程式 ax^3 + bx^2 + cx + d = 0 の解 (重解を重複して返す)
vector<double> cubic(double a, double b, double c, double d){
    auto f = [&](double x) -> double {
        return a*x*x*x + b*x*x + c*x + d;
    };

    // a を正にする
    if(a < 0){
        a *= -1;
        b *= -1;
        c *= -1;
        d *= -1;
    }

    // 解の一つを二分探索で求める
    double lb = -1e8, ub = 1e8;
    REP(_, 80){
        double x = (ub + lb) / 2;
        if(f(x) > 0){
            ub = x;
        }else if(f(x) < 0){
            lb = x;
        }
    }
    double x1 = (ub + lb) / 2;

    // 残りの二次方程式を解く
    // f(x) = (x - x1) (Ax^2 + Bx + C)
    double A = 1;
    double B = b/a + x1;
    double C = c/a + B * x1;
    vector<double> ans = quadratic(A, B, C);

    if(ans.size() == 1) ans.push_back(ans[0]); // 重解を重複して数える
    ans.push_back(x1);
    return ans;
}
