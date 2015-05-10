
typedef vector<double> Vec;
typedef vector<Vec> Mat;

// verified : AOJ 2564 Tree Reconstruction
int rank_of_matrix(Mat M){
    int H = M.size();
    int W = M[0].size();
    int cy, cx;
    for(cy = 0, cx = 0; cy < H && cx < W; cy++, cx++){
        for(int y = cy + 1; y < H; y++){
            if(abs(M[cy][cx]) < abs(M[y][cx])){
                swap(M[cy], M[y]);
            }
        }
        if(abs(M[cy][cx]) < EPS){
            cy--;
            continue;
        }
        for(int y = cy + 1; y < H; y++){
            double p = M[y][cx] / M[cy][cx];
            for(int x = cx; x < W; x++){
                M[y][x] -= p * M[cy][x];
            }
        }
    }
    return cy;
}

// verified : some problems
Vec gauss_jordan(const Mat& A, const Vec& b){
    int W = A[0].size();
    int H = A.size();

    Mat B(H, Vec(W + 1));

    for(int y = 0; y < H; y++)
        for(int x = 0; x < W; x++)
            B[y][x] = A[y][x];

    for(int y = 0; y < H; y++)
        B[y][W] = b[y];

    bool unique = true;  // 解が一意かどうか
    int cy = 0; // 現在注目している式

    // 現在注目している変数
    for(int x = 0; x < W; x++){
        int pivot = cy;
        // 注目している変数の係数の絶対値が一番大きい式を選ぶ
        for(int y = cy; y < H; y++){
            if(abs(B[y][x]) > abs(B[pivot][x])) pivot = y;
        }

        
        // 解が一意でないか,解が存在しない
        if(pivot >= H || abs(B[pivot][x]) < EPS) {
            unique = false;
            continue;
        }

        swap(B[cy], B[pivot]);

        // 注目している変数の係数を1にする
        for(int x2 = x + 1; x2 <= W; x2++) {
            B[cy][x2] /= B[cy][x];
        }


        // y番目の式からx2番目の変数を消去
        for(int y = 0; y < H; y++) if(y != cy)
            for(int x2 = x + 1; x2 <= W; x2++)
                B[y][x2] -= B[y][x] * B[cy][x2];

        // 次の式に注目する
        cy++;
    }


    // 解が存在するかどうか
    for(int y = cy; y < H; y++)
        if(abs(B[y][W]) > EPS)
            return Vec();

    // 解が複数存在するかどうか
    if(!unique) return Vec();

    // 一意な解を返す
    Vec V(W);
    int cur_x = 0;
    for(int y = 0; y < H; y++){
        if(abs(B[y][cur_x]) > EPS){
            V[cur_x++] = B[y][W];
        }
    }
    return V;
}
