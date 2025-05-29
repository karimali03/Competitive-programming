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
        if(L > R) return 1e9;
		int k = 63 - __builtin_clzll(R - L + 1);
		return min(mn[L][k], mn[R - (1 << k) + 1][k]);
	}
 
	int query_max(int L, int R) {
        if(L > R) return 1e9;
		int k = 63 - __builtin_clzll(R - L + 1);
		return max(mx[L][k], mx[R - (1 << k) + 1][k]);
	}
 
	
};

void solve(int test_case) {
    int n; cin>>n;
    vi x(n),y(n);
    f(i,0,n) cin>>x[i]>>y[i];
    if(n == 1) return void(cout<<1<<ln);
    sparse xx(x),yy(y);
    int mn = 1e18;
    for(int i = 0  ; i < n ; i++){
       vi rx(2,-1),ry(2,-1);
       if(i){
            rx[0] = xx.query_min(0,i-1); 
            rx[1] = xx.query_max(0,i-1); 
            ry[0] = yy.query_min(0,i-1);
            ry[1] = yy.query_max(0,i-1); 
       }
       if(i+1 < n){
            if(rx[0] == -1) rx[0] = xx.query_min(i+1,n-1); 
            else rx[0] = min(rx[0],xx.query_min(i+1,n-1));
            rx[1] = max(rx[1],xx.query_max(i+1,n-1));
            if(ry[0] == -1) ry[0] = yy.query_min(i+1,n-1); 
            else ry[0] = min(ry[0],yy.query_min(i+1,n-1));
            ry[1] = max(ry[1],yy.query_max(i+1,n-1));
       }
    //   debug(rx);
    //   debug(ry);
       if((rx[1]-rx[0]+1)*(ry[1]-ry[0]+1) >= n){
            mn = min(mn , (rx[1]-rx[0]+1)*(ry[1]-ry[0]+1));
       }
       else{
            int mg = 1e10;
            if(rx[0] != 0 || rx[1] != 1e9) mg = min(mg , ry[1]-ry[0]+1);
            if(ry[0] != 0 || ry[1] != 1e9) mg = min(mg , rx[1]-rx[0]+1);
            if(mg != 1e10) mn = min(mn , mg +(rx[1]-rx[0]+1)*(ry[1]-ry[0]+1) );
       }
    }
    cout<<mn<<ln; 
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