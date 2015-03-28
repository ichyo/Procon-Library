#include "../common/common.h"

template<typename Grid, typename Dist>
void grid_bfs(const Grid& grid, char sc, char wallc, Dist& dist) {
    int H = grid.size();
    assert(H > 0);
    int W = grid[0].size();
    assert(W > 0);

    assert(dist.size() >= H);
    assert(dist[0].size() >= W);
    REP(y, H) REP(x, W) dist[y][x] = INT_MAX;

    int sx = -1, sy = -1;
    REP(y, H) REP(x, W) if(grid[y][x] == sc) sx = x, sy = y;
    assert(sx != -1);

    queue<int> qx, qy;
    const vector<int> dx = {1, 0, -1, 0};
    const vector<int> dy = {0, 1, 0, -1};

    auto valid = [&](int x, int w) {
        return 0 <= x && x < w;
    };
    auto move = [&](int x, int y, int d) {
        if(!valid(x, W)) return;
        if(!valid(y, H)) return;
        if(grid[y][x] == wallc) return;
        if(dist[y][x] <= d) return;
        dist[y][x] = d;
        qx.push(x);
        qy.push(y);
    };

    move(sx, sy, 0);

    while(!qx.empty()) {
        int x = qx.front(); qx.pop();
        int y = qy.front(); qy.pop();
        int d = dist[y][x];
        REP(r, dx.size()) {
            int nx = x + dx[r];
            int ny = y + dy[r];
            int nd = d + 1;
            move(nx, ny, nd);
        }
    }
}
