typedef complex<double> P;
const double EPS = 1e-8;

// 誤差を加味した符号判定
/*
    if(a > EPS) return +1;
    if(a < -EPS) return -1;
    return 0;
*/
int sign(double x){ return x > EPS ? 1 : x < -EPS ? -1 : 0; }

// 内積・外積
double dot(P a, P b){return real(conj(a) * b);}
double cross(P a, P b){return imag(conj(a) * b);}

// OAとOBのなす符号付き角度 [-pi, pi]
// example : (1, 0), (0, 1) -> pi/2
double angle(P a, P b){return arg(conj(a) * b);}

// aをc中心にb[rad]回転
// verify : not yet.
P rotate(P a, double b, P c = P()){return (a - c) * polar(1.0, b) + c;}

/*
   if (cross(b, c) > +EPS)   return +1; // 反時計回り
   if (cross(b, c) < -EPS)   return -1; // 時計回り
   if (dot(b, c) < 0)     return +2; // c--a--b の順番で一直線上
   if (norm(b) < norm(c)) return -2; // a--b--c の順番で一直線上
   return 0;                         // 点が線分ab上にある
*/
int ccw(P a, P b, P c) {
    b -= a; c -= a;
    return sign(cross(b,c)) ? : dot(b,c) < 0 ? 2 : norm(b) < norm(c) ? -2 : 0;
}

enum{ OUT, ON, IN };

// Pointの比較をしたいときだけ定義する．
namespace std{
    bool operator < (const P& a, const P& b) {
        return a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag();
    }
};
