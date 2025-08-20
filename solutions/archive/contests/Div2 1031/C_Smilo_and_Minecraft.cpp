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


const int N = 505;
char v[N][N];
int pre[N][N];
int n,m,k; 

void init() {
    f(i,0,n+1) f(j,0,m+1) pre[i][j] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pre[i][j] = (v[i][j] == 'g')
                      + pre[i][j - 1]
                      + pre[i - 1][j]
                      - pre[i - 1][j - 1];
        }
    }
}

int query(int from_x,int from_y,int to_x,int to_y) {
    from_x = max(1ll , from_x); from_y = max(1ll , from_y);
    to_x = min(n , to_x);  to_y = min( m , to_y);
    return pre[to_x][to_y] - pre[from_x - 1][to_y] 
           - pre[to_x][from_y-1] + pre[from_x-1][from_y-1]; 
}

void solve(int test_case) {
    cin>>n>>m>>k;
    f(i,1,n+1) f(j,1,m+1) cin>>v[i][j];
    init();
    int cnt= 0 ;
    int mx = 0;
    f(i,1,n+1) f(j,1,m+1) if(v[i][j] == 'g') cnt++; 
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j  <= m ; j++){
            if(v[i][j] == '.'){
                int res = cnt - query(i-k+1,j-k+1,i+k-1,j+k-1);
                mx = max(mx,res);
            }
        }
    }
    cout<<mx<<ln;
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