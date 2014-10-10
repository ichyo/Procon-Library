#include "../common/common.h"
// Suffix Array (プログラミングコンテストチャレンジブック 2nd edition p.335)
namespace SA{
    const int MAX_N = 1000000; // 入力文字列の最大長

    int n, k;
    int rank[MAX_N + 1];
    int tmp[MAX_N + 1];

    // (rank[i], rank[i + k]) と (rank[j], rank[j + k]) を比較
    bool comp(int i, int j){
        if(rank[i] != rank[j]) return rank[i] < rank[j];
        int ri = i + k <= n ? rank[i + k] : -1;
        int rj = j + k <= n ? rank[j + k] : -1;
        return ri < rj;
    }

    vector<int> buildSA(const string& s){
        n = s.size();
        vector<int> sa(n + 1);

        // 最初は1文字, ランクは文字コードにすればよい
        for(int i = 0; i <= n; i++){
            sa[i] = i;
            rank[i] = i < n ? s[i] : -1;
        }

        // k文字についてソートされているところから、2k文字でソートする
        for(k = 1; k <= n; k *= 2){
            sort(sa.begin(), sa.end(), comp);

            tmp[sa[0]] = 0;
            for(int i = 1; i <= n; i++){
                tmp[sa[i]] = tmp[sa[i - 1]] + (comp(sa[i - 1], sa[i]) ? 1 : 0);
            }
            for(int i = 0; i <= n; i++){
                rank[i] = tmp[i];
            }
        }

        return sa;
    }

    vector<int> buildLCP(string s, const vector<int>& sa){
        n = s.size();
        vector<int> lcp(n);

        for(int i = 0; i <= n; i++) rank[sa[i]] = i;

        int h = 0;
        lcp[0] = 0;
        for(int i = 0; i < n; i++){
            // 文字列中での位置iの接尾辞と、接尾辞配列中でその一つ前の接尾辞のLCPを求める
            int j = sa[rank[i] - 1];

            // hを先頭の分1減らし、後ろが一致しているだけ増やす
            if(h > 0) h--;
            for(; j + h < n && i + h < n; h++){
                if(s[j + h] != s[i + h]) break;
            }

            lcp[rank[i] - 1] = h;
        }

        return lcp;
    }
}
