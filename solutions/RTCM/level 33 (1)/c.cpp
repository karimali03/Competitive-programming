#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}


 struct sparse {
	vector<vector<int>> mn, mx;
	int n;
 
	sparse(vector<int>& v) {
		n = v.size();
		int LOG = 64 - __builtin_clzll(n); // ensures log2(n) + 1
		mn = mx  = vector<vector<int>>(n, vector<int>(LOG));
 
		for (int i = 0; i < n; i++) {
			mn[i][0] = mx[i][0] = v[i];
		}
 
		for (int k = 1; (1 << k) <= n; k++) {
			for (int i = 0; i + (1 << k) <= n; i++) {
				mn[i][k] = min(mn[i][k - 1], mn[i + (1 << (k - 1))][k - 1]);
				mx[i][k] = max(mx[i][k - 1], mx[i + (1 << (k - 1))][k - 1]);	
			}
		}
	}
 
	int query_min(int L, int R) {
		int k = 63 - __builtin_clzll(R - L + 1);
		return min(mn[L][k], mn[R - (1 << k) + 1][k]);
	}
 
	int query_max(int L, int R) {
		int k = 63 - __builtin_clzll(R - L + 1);
		return max(mx[L][k], mx[R - (1 << k) + 1][k]);
	}
 
	
};



void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n); cin>>a>>b;
    int m; cin>>m;
    vi v(m); cin>>v;
    for(int i = 0 ; i < n ; i++){
        if(b[i] > a[i]){
            NO; return;
        }
    }
    map<int,vi>mp;
    map<int,int>cnt;
    for(int i = 0  ;i < m ; i++) cnt[v[i]]++;
    for(int i = 0 ; i < n ; i++){
        if(a[i] != b[i]) mp[b[i]].push_back(i);
    }
    sparse st(b);
    for(auto &[x,y] : mp){
        int req = 0;
        int sz = y.size();
        for(int i = 0 ; i < sz ; i++ ){
            if(i == sz-1 || (st.query_max(y[i],y[i+1]) > x )) req++;
        }
        if(req > cnt[x]){
            NO; return;
        }
    }
    YES;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}