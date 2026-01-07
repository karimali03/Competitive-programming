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

char dir[] = {'U','D','R','L'};
int ask(int idx,int k){
    cout<<"? "<<dir[idx]<<" "<<k<<endl;
    int ret; cin>>ret;
    return ret;
}

void answer(int x,int y){
    cout<<"! "<<x<<" "<<y<<endl;
}

void solve(int test_case) {
    int n; cin>>n; 
    vec<pair<int,int>>v(n);
    f(i,0,n) cin>>v[i].first>>v[i].second;
    
    for(int i = 0 ; i < 3 ; i++) ask(2,1e9); // 3 r
    ask(0,1e9);
    int res = ask(0,1e9); // 2 u 
    pair<int,int> imag = {2e15,2e15};
    int mn = INT64_MAX;
    int idx = 0;
    for(int i = 0 ;i  < n ; i++){
        int ac = abs(imag.first-v[i].first) + abs(imag.second-v[i].second);
        if(ac < mn){
            mn = ac;
            idx = i;
        }
    }
    for(int i = 0 ; i < 3 ; i++) ask(1,1e9);
    int res2 = ask(1,1e9); // 4 d
    imag = {2e15,-2e15};
    mn = INT64_MAX;
    int idx2 = 0;
    for(int i = 0 ;i  < n ; i++){
        int ac = abs(imag.first-v[i].first) + abs(imag.second-v[i].second);
        if(ac < mn){
            mn = ac;
            idx2 = i;
        }
    }
    int x = (res + res2 - 3 * 2 * 1e9 - 2 * 2 * 1e9 + v[idx].first + v[idx2].first + v[idx].second - v[idx2].second )/ 2;
    int y = (res - x - 3 * 1e9 + v[idx].first + v[idx].second - 2 * 1e9);
    answer(x,y);

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