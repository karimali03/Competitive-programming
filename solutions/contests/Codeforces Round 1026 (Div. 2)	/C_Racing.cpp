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


// intersect two segments
bool intersect(pair<int,int> a, pair<int,int> b) {
    if (a.first > b.first) swap(a, b);
    return a.second >= b.first;
}


void solve(int test_case) {
    int n; cin>>n;
    vi d(n); cin>>d;
    vii rng(n,vi(2));
    f(i,0,n) cin>>rng[i];
    vii x(n,vi(2));
    for(int i = 0 ; i < n ; i++){
        if(i) x[i][0]+=x[i-1][0],x[i][1]+=x[i-1][1];
        if(d[i] != -1){
            x[i][0]+=d[i];
            x[i][1]+=d[i];
        }
        else {
            x[i][1]++;
        }
        if(!intersect({x[i][0],x[i][1]},{rng[i][0],rng[i][1]}))
        return void(cout<<-1<<ln);
        x[i][0] = max(x[i][0],rng[i][0]);
        x[i][1] = min(x[i][1],rng[i][1]);
    }
    vi res(n);
  //  for(int i  = 0 ; i < n ; i++) {debug(x[i]);}
    int cur = x[n-1][1];
    for(int i = n-1 ; i >= 0 ; i--){
        if(d[i] == -1){
            if(i == 0){
                if(cur == 1) res[i] = 1;
                else res[i] = 0;
            }
            else{
                if(x[i-1][1] >= cur) res[i] = 0;
                else res[i] = 1;
            }
            cur-=res[i];
        }
        else{
            cur-=d[i];
            res[i] = d[i];
        }
    }
    for(int i = 0 ; i < n  ; i++) cout<<res[i]<<" ";
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