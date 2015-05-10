// Z Algorithm O(n)
// 1..n-1の範囲でz[i] := s[0..] と s[i..]のマッチする長さのベクタを返す。z[0] は 0
vector<int> Z_Algorithm(const string& s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i > r) {
            l = r = i;
            while (r < n && s[r-l] == s[r]){ r++; }
            z[i] = r-l;
            r--;
        } else {
            int k = i-l;
            if (z[k] < r-i+1){
                z[i] = z[k];
            } else {
                l = i;
                while (r<n && s[r-l] == s[r]){ r++; }
                z[i] = r-l;
                r--;
            }
        }
    }
    return z;
}

