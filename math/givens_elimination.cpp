#include "../common/common.h"
// Givens消去法(QR分解)
// 説明
// n x nの正方行列Aとベクトルbを入力として，
// A x = bをみたすベクトルxを返す．
// この実装ではrankA = nを仮定している．
//
// 計算量
// O(n ^ 3)
//
// 使い方
// [Matrix A]
//   n x n の行列A
// [Vector b]
//   要素数nのベクトルb
// 
// Verified
// AOJ 2171 Strange Couple

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

// [r, 0]を[x, y]に変換するc, sを計算する
inline void make_param(double x, double y, double& c, double &s){
    double r = sqrt(x * x + y * y);
    c = x / r, s = y / r;
}
// 回転行列[[c, s], [-s, c]]を[x, y]に適用する
inline void rotate(double& x, double& y, double c, double s){
    double u = c * x + s * y;
    double v = -s * x + c * y;
    x = u, y = v;
}

// Ax = bを解く
Vector givens_elimination(Matrix A, Vector b){
    int n = A.size();
    for(int i = 0; i < n; i++){
        for(int i2 = i + 1; i2 < n; i2++){
            double c, s;
            make_param(A[i][i], A[i2][i], c, s);
            rotate(b[i], b[i2], c, s);
            for(int j = i; j < n; j++){
                rotate(A[i][j], A[i2][j], c, s);
            }
        }
    }
    for(int i = n - 1; i >= 0; i--){
        b[i] /= A[i][i];
        for(int j = i - 1; j >= 0; j--){
            b[j] -= A[j][i] * b[i];
        }
    }
    return b;
}
