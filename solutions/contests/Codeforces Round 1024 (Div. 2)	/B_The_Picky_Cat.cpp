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

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    int val = v[0];
    sort(all(v));
    int idx = 0;
    for(int i = 0 ; i < n ; i++) if(v[i] == val) idx=i;
    int dis = idx -  (n-1)/2;
    if(dis == 0 || v[(n-1)/2] == val ){
        cout<<"YES"<<ln;
        return;
    } 
    else if(dis > 0){
        for(int i = 0 ; i < idx ; i++) if(-v[i] >= v[idx]) dis--;
        if(dis <= 0) return void(cout<<"YES\n");
    }
    else{
        for(int i = n-1 ; i > idx ; i--) if(-v[i] <= v[idx]) dis++;
        if(dis >= 0) return void(cout<<"YES\n");
    }
    v[idx] = -val;
    val = -val;
    sort(all(v));
    if(v[(n-1)/2] == val) return void(cout<<"YES\n");
    for(int i = 0 ; i < n ; i++) if(v[i] == val) idx=i;
    dis = idx - (n-1)/2;
    if(dis == 0){
        cout<<"YES"<<ln;
        return;
    } 
    else if(dis > 0){
        for(int i = 0 ; i < idx ; i++) if(-v[i] >= v[idx]) dis--;
        if(dis <= 0) return void(cout<<"YES\n");
    }
    else{
        for(int i = n-1 ; i > idx ; i--) if(-v[i] <= v[idx]) dis++;
        if(dis >= 0) return void(cout<<"YES\n");
    }
    cout<<"NO\n";
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