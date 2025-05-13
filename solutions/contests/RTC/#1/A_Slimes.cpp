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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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


int query_sum(int l,int r,vi& pre){
    return pre[r] - (l ? pre[l-1] : 0);
}
vector<int> sol(int n,vi &v){
    vi res(n,INT64_MAX);
    sparse st(v);
    vi pre(n);
    f(i,0,n) pre[i] = v[i] + (i?pre[i-1]:0);
    for(int i = 1  ; i < n ; i++){
        if(v[i-1] > v[i]) res[i] = 1;
        else {
            int l = 0, r = i-2;
            int ans = -1;
            while(l <= r){
                int mid = l + (r-l)/2;
                if( query_sum(mid,i-1,pre) > v[i] &&  st.query_min(mid,i-1) != st.query_max(mid,i-1)){
                    l = mid+1;
                    ans = mid;
                  
                }
                else r = mid-1;
            }
            if(ans != -1)  res[i] = i - ans;
        }
    
    }
    return res;
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    stack<int>st;
    auto r1 = sol(n,v);
 
    reverse(all(v));
   
    auto r2 = sol(n,v);
    reverse(all(r2));
   
    f(i,0,n) r1[i] = min(r1[i],r2[i]);

    f(i,0,n){
        if(r1[i] == INT64_MAX) cout<<-1<<" ";
        else cout<<r1[i]<<" ";
    }
    cout<<ln;
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