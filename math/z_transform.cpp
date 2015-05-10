
void transform1(int N, int a[]){
    // 変換前 a[S] := f(S)
    // 変換後 a[S] := sum of f(T). T is subset of S.
    REP(i, N)REP(S, 1 << N){
        if(0 == (S & (1 << i))){
            a[S | 1 << i] += a[S];
        }
    }
}

void transform2(int N, int a[]){
    // 変換前 a[S] := f(S)
    // 変換後 a[S] := sum of f(T). T is superset of S.
    REP(i, N)REP(S, 1 << N){
        if(0 == (S & (1 << i))){
            a[S] += a[S | (1 << i)];
        }
    }
}
