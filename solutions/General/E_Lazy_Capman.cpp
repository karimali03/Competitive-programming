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


vector<int> NGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,-1);
    for(int i = 0 ; i < n ; i++){
        while(!st.empty() && v[st.top()] < v[i]){ // > for NSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> PGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,-1);
    for(int i = n-1 ; i >= 0 ; i--){
        while(!st.empty() && v[st.top()] < v[i]){ // > for PSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
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
    int n,k; cin>>n>>k;
    vi a(n),b(n); cin>>a>>b;
    vi segmentB(n-k+1) , segmentA(n-k+1);
    int sumB = 0 , sumA = 0;
    for(int i = 0 ;i  < n ; i++){
        sumB += b[i]; sumA += a[i];
        if(i-k >= 0) sumB-=b[i-k] , sumA -= a[i-k];
        if(i-k+1 >= 0) segmentB[i-k+1] = sumB , segmentA[i-k+1] = sumA;
    }
    vi pre(n);
    for(int i = 0 ; i < n ; i++){
        pre[i] = b[i] - a[i];
        if(i) pre[i] += pre[i-1];
    }
    sparse st(pre);
 
    auto ng = NGE(segmentB);
    auto pg = PGE(segmentB);
    int res = INT64_MIN;
    for(int i = 0 ; i < n-k+1 ; i++){
        int l = pg[i]+1;
        int r = ng[i] == -1 ? n-1 : ng[i]-1+k-1;
        int ans = -segmentA[i];
        if(i){
            int ch = pre[i-1] - st.query_min(max(0ll,l-1),i-1);
            if(l == 0) ch = max(ch , pre[i-1]);
            ans += ch;
        }
        if(i+k <= r){
            ans += max(0ll , st.query_max(i+k,r) - pre[i+k-1]);
        }  
      //  cout<<l<<" "<<r<<" "<<ans<<ln;
        res = max(res , ans);
    }
    cout<<res<<ln;
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