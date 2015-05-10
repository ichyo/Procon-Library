// サイコロ
enum FACE { TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT };

struct Dice {
    vector<int> val;
    Dice(vector<int> init) : val(init) {
        assert(val.size() == 6);
    }
    void roll_x() { 
        roll(TOP, BACK, BOTTOM, FRONT);
    }
    void roll_y() {
        roll(TOP, LEFT, BOTTOM, RIGHT);
    }
    void roll_z() {
        roll(FRONT, RIGHT, BACK, LEFT);
    }
    void roll_r(int r){
        if(r == 0) roll(TOP, LEFT, BOTTOM, RIGHT); // 右
        if(r == 1) roll(TOP, BACK, BOTTOM, FRONT); // 下
        if(r == 2) roll(TOP, RIGHT, BOTTOM, LEFT); // 左
        if(r == 3) roll(TOP, FRONT, BOTTOM, BACK); // 上
    }
    void roll(int a, int b, int c, int d){ // a, b, c, d -> b, c, d, a
        int tmp = val[a];
        val[a] = val[b]; val[b] = val[c];
        val[c] = val[d]; val[d] = tmp;
    }
};

vector<Dice> all_roll(Dice a){
    vector<Dice> dices;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            dices.push_back(a);
            a.roll_z();
        }
        if(i & 1) a.roll_x();
        else a.roll_y();
    }
    return dices;
}
