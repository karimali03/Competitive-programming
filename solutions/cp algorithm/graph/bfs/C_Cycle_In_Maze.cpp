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


bool valid(int i,int j,int n,int m ,vec<string>&v){
    return i >= 0 && j >= 0 && i < n && j < m && v[i][j] != '*';
}
void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    vec<string>v(n);
    f(i,0,n) cin>>v[i];
    if(k&1) return void(cout<<"IMPOSSIBLE\n");
    string res;
    int len = 0;
    int x,y;
    f(i,0,n) f(j,0,m) if(v[i][j] == 'X') x=i,y=j;
    int xx = x , yy = y;
    while(len < k/2){
        int c = 0;
        while(len < k/2 && valid(x+1,y,n,m,v)) res.push_back('D'),x++,len++,c++;
        while(len < k/2 && valid(x,y-1,n,m,v)) res.push_back('L'),y--,len++,c++;
        if(c) continue;;
        while(len < k/2 && valid(x,y+1,n,m,v)) res.push_back('R'),y++,len++,c++;
        if(c) continue;
        while(len < k/2 && valid(x-1,y,n,m,v)) res.push_back('U'),x--,len++,c++;
        if(!c) return void(cout<<"IMPOSSIBLE\n");
    }  
    cout<<res;

    cout<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}