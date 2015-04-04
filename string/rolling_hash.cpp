#include "../common/common.h"
typedef unsigned long long ULL;

// mod 2^64 の ローリングハッシュ (衝突させられるから通常は使用しない)
template<ULL B>
struct RHash{
    vector<ULL> pow; 
    vector<ULL> hash;
    RHash(const string& s) {
        int n = s.size();
        pow.assign(n + 1, 1);
        hash.assign(n + 1, 0);
        REP(i, n) {
            pow[i + 1] = pow[i] * B;
            hash[i + 1] = s[i] + hash[i] * B;
        }
    }
    // hash of s[0..i)
    ULL h(int i) {
        return hash[i];
    }
    // hash of s[i..j)
    ULL h(int i, int j) {
        if(i == 0) return h(j);
        return h(j) - h(i) * pow[j-i];
    }
};

// MODを指定できるローリングハッシュ．(普段はこれを使う) (ref. http://hos.ac/blog/)
template<int B, int M>
struct RMHash{
    vector<int> pow;
    vector<int> hash;
    RMHash(const string& s) {
        int n = s.size();
        pow.assign(n + 1, 1);
        hash.assign(n + 1, 0);
        REP(i, n) {
            pow[i + 1] = ((long long)pow[i] * B) % M;
            hash[i + 1] = (s[i] + (long long)hash[i] * B % M) % M;
        }
    }
    // hash of s[0..i)
    int h(int i) {
        return hash[i];
    }
    // hash of s[i..j)
    int h(int i, int j) {
        if(i == 0) return h(j);
        int res = (h(j) - (long long)h(i) * pow[j-i]) % M;
        if(res < 0) res += M;
        return res;
    }
};

// --- 
// a が b に含まれているか
bool contain(string a, string b) {
    typedef RHash<1000000007> Hash;
    int al = a.size(), bl = b.size();
    if(al > bl) return false;

    Hash A(a);
    ULL ah = A.h(al);

    Hash B(b);
    for(int i = 0; i + al <= bl; i++) {
        if(B.h(i, i + al) == ah) {
            return true;
        }
    }
    return false;
}
