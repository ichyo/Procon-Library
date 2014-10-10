#include "../common/common.h"
// 最大共通部分列 (longest common sequence)
// 計算量: O(nm)
vector<int> lcs(const vector<int>& a, const vector<int>& b){
    // dp part
    const int MAX_L = 1000;
    int dp[MAX_L + 1][MAX_L + 1] = {};
    int type[MAX_L + 1][MAX_L + 1] = {};
    for(int i = 0; i < a.size(); i++)
    for(int j = 0; j < b.size(); j++){
        if(a[i] == b[j]){
            dp[i + 1][j + 1] = dp[i][j] + 1;
            type[i + 1][j + 1] = 0;
        }else if(dp[i + 1][j] < dp[i][j + 1]){
            dp[i + 1][j + 1] = dp[i][j + 1];
            type[i + 1][j + 1] = 1;
        }else{
            dp[i + 1][j + 1] = dp[i + 1][j];
            type[i + 1][j + 1] = 2;
        }
    }

    // restore part
    vector<int> res;
    for(int i = a.size(), j = b.size(); i > 0 && j > 0;){
        if(type[i][j] == 0){
            i--; j--;
            res.push_back(a[i]);
        }else if(type[i][j] == 1){
            i--;
        }else if(type[i][j] == 2){
            j--;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}
