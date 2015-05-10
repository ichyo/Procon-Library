class Pazzle15{
    static const int H = 4;
    static const int W = 4;
    static constexpr int dx[4] = {1, 0, -1, 0};
    static constexpr int dy[4] = {0, 1, 0, -1};
    int a[4][4];
    int zx, zy;

    Pazzle15(int init[H][W]) {
        REP(y, H) REP(x, W) a[y][x] = init[y][x];
        REP(y, H) REP(x, W) if(a[y][x] == 0) zx = x, zy = y;
    }

    int h() {
        int res = 0;
        REP(y, H) REP(x, W) {
            int v = a[y][x] - 1;
            if(v == -1) continue;
            int gx = v % W;
            int gy = v / W;
            res += abs(gx - x) + abs(gy - y);
        }
        return res;
    }

    int ans;
    int step;
    bool updated;
    int key[1000];
    int move[1000];
    int ans_key[1000];
    void dfs() {
        const int hr = h();
        if(step + hr >= ans) return;

        if(hr == 0) {
            ans = step;
            REP(i, ans) ans_key[i] = key[i+1];
            updated = true;
            return;
        }

        REP(r, 4) if(r != move[step]) {
            const int nx = zx + dx[r];
            const int ny = zy + dy[r];
            if(nx >= 0 && nx < W && ny >= 0 && ny < H) {
                step++;
                swap(a[zy][zx], a[ny][nx]);
                key[step] = a[zy][zx];
                move[step] = r;

                dfs();

                swap(a[zy][zx], a[ny][nx]);
                step--;
            }
        }
    }
    int solve() {
        ans = 1;
        step = 0;
        updated = false;
        while(true) {
            assert(step == 0);
            key[0] = move[0] = -1;
            dfs();
            if(updated) return ans;
            ans++;
        }
    }
};

