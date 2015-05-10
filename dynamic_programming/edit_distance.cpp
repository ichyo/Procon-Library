int edit_distance(const string& a, const string& b){
    int n = a.size(), m = b.size();

    const int MAX_L = 1000;
    int dp[MAX_L + 1][MAX_L + 1] = {};
    int type[MAX_L + 1][MAX_L + 1] = {}; // 0 - nothing, 1 - remove, 2 - add, 3 - replace

    for(int i = 1; i <= n; i++){
        dp[i][0] = i;
        type[i][0] = 1;
    }

    for(int j = 1; j <= m; j++){
        dp[0][j] = j;
        type[0][j] = 2;
    }

    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){
        if(a[i] == b[j]){
            dp[i + 1][j + 1] = dp[i][j];
        }else{
            dp[i + 1][j + 1] = min({dp[i][j + 1] + 1, dp[i + 1][j] + 1, dp[i][j] + 1});

        }

        // for restoring
        if(a[i] == b[j]){
            type[i + 1][j + 1] = 0; // do nothing
        }else if(dp[i + 1][j + 1] == dp[i][j + 1] + 1){
            type[i + 1][j + 1] = 1; // remove
        }else if(dp[i + 1][j + 1] == dp[i + 1][j] + 1){
            type[i + 1][j + 1] = 2; // add 
        }else {
            type[i + 1][j + 1] = 3; // replace 
        }
    }

    // aからbの変換手順を復元 (s = a)
    for(int i = n, j = m; i > 0 || j > 0;){
        if(type[i][j] == 0){
            i--; j--;
            // do nothing
        }else if(type[i][j] == 1){
            i--;
            // remove a[i] (s.erase(s.begin() + i))
        }else if(type[i][j] == 2){
            j--;
            // insert b[j] (s.insert(s.begin() + i, b[j]))
        }else if(type[i][j] == 3){
            i--; j--;
            // replace a[i] to b[j] (s[i] = b[j])
        }
    }

    return dp[n][m];
}
