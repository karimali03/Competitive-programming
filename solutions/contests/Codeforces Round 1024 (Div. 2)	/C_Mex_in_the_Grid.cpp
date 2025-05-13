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
    vii v(n,vi(n,-1));
    int val = 1;
    v[(n-1)/2][(n-1)/2] = 0;
    
    for(int a = (n-1)/2+1 ; a < n ; a++){
        int r1 = a,j1 = (n-1)/2;
        int r2 = (n-1)/2,j2 = a;
        while(true){
            v[r2][j2] = val++;
            if(r1 == r2 && j1 == j2) break;
            v[r1][j1] = val++;
           r2++,j1++;
        }
    }

    for(int a = (n-1)/2-1 ; a >= 0 ; a--){
        int r2 = (n-1)/2,j2 = a;
        while(true){
            v[r2][j2] = val++;
            r2++;
            if(r2 >= n ) break;
        }
        
    }
    
    for(int a = (n-1)/2-1 ; a >= 0 ; a--){
        int r1 = a,j1 = (n-1)/2;
        while(true){
            v[r1][j1] = val++;
            j1++;
            if(j1 >= n ) break;
        }
    }

    f(i,0,n) f(j,0,n) if(v[i][j] == -1) v[i][j] = val++;
    f(i,0,n){
        f(j,0,n) cout<<v[i][j]<<" ";
        cout<<ln;
    }

   

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