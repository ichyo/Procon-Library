// 1年1月1日からy年m月d日までの日数を計算する(y = 1, m = 1, d = 1 は 1 が返ってくる)
int days(int y, int m, int d) {
    if(m <= 2){ y--; m += 12; }
    return 365*y + y/4 - y/100 + y/400 + 153*(m+1)/5 + d - 428;
}
