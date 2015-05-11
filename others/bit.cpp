#include "../common/common.h"

void combination(int n, int k) {
    // nCkのビットコンビネーションを辞書順で列挙する
    for(int comb = (1 << k) - 1; comb < (1 << n);){
        // do something here
        int x = comb & -comb, y = comb + x;
        comb = ((comb & ~y) / x >> 1) | y;
    }
}

void subset(int sup) {
    // 集合supの部分集合subを列挙する
    int sub = sup;
    do{
        // do something here
        sub = (sub - 1) & sup;
    } while(sub != sup);
}

/* int __builtin_clz(unsigned int);      | 最上位ビットから数えて0の連続する個数
 * int __builtin_ctz(unsigned int);      | 最下位ビットから数えて0の連続する個数
 * int __builtin_popcount(unsigned int); | 2進数表記中に出現する1の個数
 * int __builtin_ffs(unsigned int);      | 最下位ビットから数えて最初に出現する1の位置
 * - unsigned long longのときは，関数名の末尾にllを加える
 * - 0に対する動作が未定義なことに注意する
 */
