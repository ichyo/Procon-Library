#include "../common/common.h"
// 0-1ナップサック問題(近似アルゴリズム) (https://gist.github.com/spaghetti-source/9565504_)
//
// 概要:
// 0-1ナップサック問題を解くアルゴリズム．
// 0-1ナップサック問題はアイテムは1度しか使えないナップサック問題．
// このライブラリは嘘解法，近似アルゴリズムなので注意．
// 落とすのは難しいらしい．
//
// 計算量:
// ???
//
// 使い方:
// Knapsack solver;
// /* アイテムを追加 (価値, 重み) *;/
// solver.add_item(1, 2);
// solver.add_item(3, 4);
// /* 重みを指定して最大の価値を出力 */
// cout << solver.solve(W) << endl;
//

class Knapsack {
    typedef long long LL;
    struct item { 
        LL v, w; 
    };

    LL W;
    vector<item> items;
    LL lv;

    LL solve_rec(size_t k, LL v, LL w) {
        if (w + items[k].w > W) return solve_rec(k+1, v, w);
        LL cv = v, cw = w;
        for (size_t i = k; i < items.size(); ++i) {
            if (cw + items[i].w <= W) {
                cw += items[i].w;
                cv += items[i].v;
            }
        }
        if (lv < cv) lv = cv;
        double fv = v, fw = w;
        for (size_t i = k; i < items.size(); ++i) {
            if (fw + items[i].w <= W) {
                fw += items[i].w;
                fv += items[i].v;
            } else {
                fv += items[i].v * (W - fw) / items[i].w;
                break;
            }
        }
        if (fv - lv < 1 || fv < lv) return lv;
        solve_rec(k+1, v+items[k].v, w+items[k].w);
        return solve_rec(k+1, v, w);
    }

    public:
    // 価値v, 重みwのアイテムを追加
    void add_item(LL v, LL w) {
        items.push_back({v, w});
    }

    // 重みの合計がW以下になるようにアイテムを選んだときの価値の和の最大値を返す．
    LL solve(LL W_) {
        if(items.empty()) return 0;
        W = W_;
        sort(items.begin(), items.end(), [](const item &a, const item &b) { 
                return a.v * b.w > a.w * b.v;
                });
        lv = 0;
        return solve_rec(0, 0, 0);
    };
};

