#include "../common/common.h"

// 単調関数 f の零点を [l, r] の範囲で求める
double find_root(double l, double r, double f(double)){
    int sign = (f(l) > 0 ? +1 : -1);
    REP(_, 50) {
        double x = (l + r) / 2;
        if(sign * f(x) > 0) {
            l = x;
        } else {
            r = x;
        }
    }
    return (l + r) / 2;
}

// 凸関数 f の極大値を [a, b] の範囲で求める
double find_max(double a, double b, double f(double)) {
    REP(_, 86) {
        double c = (a * 2 + b) / 3;
        double d = (a + b * 2) / 3;
        if(f(c) > f(d)) { // '>': maximum, '<': minimum
            b = d;
        } else {
            a = c;
        }
    }
    return (a + b) / 2;
}
