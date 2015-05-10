
// 区間[l, r]をN分割し、各区間を2次関数に近似する
// 計算時間: O(N * f(x))
double simpson(double l, double r, int N, double f(double)){
    double h = (r - l) / (2 * N); 
    double S = f(l) + f(r);
    for(int i = 1; i < 2 * N; i += 2){
        S += 4.0 * f(l + h * i);
    }
    for(int i = 2; i < 2 * N; i += 2){
        S += 2.0 * f(l + h * i);
    }
    return S * h / 3.0;
}

