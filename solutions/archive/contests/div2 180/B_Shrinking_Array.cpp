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

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    int ret = n+1;
    for(int i = 0 ; i <  n-1 ;i++){
        if(abs(v[i]-v[i+1]) <= 1){
            cout<<0<<ln;
            return;
        }
    }
    for(int i  = 0  ; i <  n; i++){
        int mn = -1 , mx = -1;
        for(int j = i+1 ; j < n ; j++){
            if(mx == -1 && v[j] >= v[i]){
                mx = j;
            }
            if(mn == -1 && v[j] <= v[i]){
                mn = j;
            }
        }
        if(mn != -1 && mx != -1){
            ret = min(ret , max(mx,mn)-i - 1);
        }
        mx = mn = -1;
        for(int j = i-1; j >= 0 ; j-- ){
              if(mx == -1 && v[j] >= v[i]){
                mx = j;
            }
            if(mn == -1 && v[j] <= v[i]){
                mn = j;
            }
        }
        if(mn != -1 && mx != -1){
            ret = min(ret , i - min(mx,mn) - 1);
        }
    }
    for(int i = 0  ; i <  n ;i++){
        for(int j = 0 ; j <  n ; j++){
            if(i != j && (abs(v[j]-v[i]) <= 1 ) ){
                ret = min(ret , abs(i-j) - 1);
            }
        }
    }
    if(ret != n+1)
    cout<<ret<<ln;
    else NA;   
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