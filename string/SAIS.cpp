// This code were originally copied from zerokugi's code (http://codeforces.com/contest/526/submission/10585724).
#include "../common/common.h"

class SuffixArray{
private:
	template <bool End, typename T>
	vector<int> compute_buckets(const T *s, int n, int k) const {
		vector<int> buckets(k);
		REP(i, n) ++buckets[s[i]];
		int sum = 0;
		REP(i, k){
			sum += buckets[i];
			buckets[i] = (End ? sum : (sum - buckets[i]));
		}
		return buckets;
	}

	template <typename T>
	void induce_sa_l(int *sa, const T *s, int n, int k, const vector<int> &ls) const {
		vector<int> buckets(compute_buckets<false>(s, n, k));
		REP(i, n){
			const int j = sa[i] - 1;
			if(j >= 0 && !ls[j]){ sa[buckets[s[j]]++] = j; }
		}
	}

	template <typename T>
	void induce_sa_s(int *sa, const T *s, int n, int k, const vector<int> &ls) const {
		vector<int> buckets(compute_buckets<true>(s, n, k));
        for(int i = n-1; i >= 0; i--) {
			const int j = sa[i] - 1;
			if(j >= 0 && ls[j]){ sa[--buckets[s[j]]] = j; }
		}
	}

	bool is_lms(const vector<int>& ls, int i)const {
		return i>0 && !ls[i-1] && ls[i];
	}
	
	template <typename T>
	void sa_is(int *sa, const T *s, int n) const{
		vector<int> ls(n); // 0:L 1:S
		ls[n-1] = 1;
        for(int i = n-2; i >= 0; i--) {
		    ls[i] = (s[i] != s[i+1]) ? s[i] < s[i+1] : ls[i+1];
        }
		const int k = (int)*std::max_element(s, s + n) + 1;
		vector<int> buckets = compute_buckets<true>(s, n, k);
		REP(i, n) sa[i] = -1;
        for(int i = 1; i < n; i++) {
		    if(is_lms(ls, i)) sa[--buckets[s[i]]] = i;
        }
		induce_sa_l(sa, s, n, k, ls);
		induce_sa_s(sa, s, n, k, ls);
		int m = 0;
		REP(i, n) if(is_lms(ls, sa[i])) sa[m++] = sa[i];
		for(int i=m;i<n;i++) sa[i] = -1;
		int num = 0, prev = -1;
		REP(i, m){
			int p = sa[i], diff = 0;
			REP(d, n){
				const int l = p+d, r = prev + d;
				if(prev < 0 || s[l] != s[r] || ls[l] != ls[r]){
					diff = 1;
					break;
				}else if(d > 0 && (is_lms(ls, l) || is_lms(ls, r))){
					break;
				}
			}
			if(diff){
				num ++;
				prev = p;
			}
			p = (p-(p&1))/2;
			sa[m+p] = num-1;
		}
		for(int i=n-1, j=n-1;i>=m;i--) if(sa[i] >= 0) sa[j--]=sa[i];
		int *reduced_s = sa+n-m;
		if(num < m) sa_is(sa, reduced_s, m);
		else REP(i, m) sa[reduced_s[i]] = i;
		buckets = compute_buckets<true>(s, n, k);
		int j=0;
        for(int i = 1; i < n; i++) {
		    if(is_lms(ls, i)) reduced_s[j++] = i;
        }
		REP(i, m) sa[i] = reduced_s[sa[i]];
		for(int i=m;i<n;i++) sa[i] = -1;
        for(int i = m-1; i >= 0; i--) {
			const int p = sa[i];
			sa[i] = -1;
			sa[--buckets[s[p]]] = p;
		}
		induce_sa_l(sa, s, n, k, ls);
		induce_sa_s(sa, s, n, k, ls);
	}
	
	vector<int> _sa;

	template <typename T>
	vector<int> sa_is(const T &s) const {
		if(s.size() == 0){ return vector<int>(1); }
		const int n = s.size() + 1;
		vector<int> vs(n), sa(n);
		REP(i, n-1){ vs[i] = s[i]; }
		sa_is(&sa[0], &vs[0], n);
		return sa;
	}

public:
	template <typename T>
	explicit SuffixArray(const T &s): _sa(sa_is(s)) {}

	size_t size() const { return _sa.size(); }

	inline int operator[](int i) const { return _sa[i]; }

    const vector<int>& array() const { return _sa; }
};

struct LCP{
	int n;
	vector<int> vs, isa, lcp;
public:
	template <typename T>
	LCP(const T &s, const vector<int>& sa):
        n(sa.size()), vs(n), isa(n), lcp(n-1){
        REP(i, n-1) vs[i] = s[i];
        REP(i, n) isa[sa[i]] = i;
        int h = 0, j;
        REP(i, n)if((j = isa[i]) > 0){
            while(vs[sa[j] + h] == vs[sa[j-1] + h]) h++;
            lcp[j-1] = h;
            if(h > 0) --h;
        }
	}

	size_t size() const { return lcp.size(); }

	inline int operator[](int i) const { return lcp[i]; }

    const vector<int>& array() const { return lcp; }
};
