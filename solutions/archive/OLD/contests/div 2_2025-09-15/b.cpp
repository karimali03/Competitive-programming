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
    set<int>a,b,c;
    f(i,0,n) c.insert(i+1);
    for(int i = 0 ; i < n ; i++){
        if(v[i] != i+1 && v[i] != 0) a.insert(v[i]),b.insert(i);
        if(v[i]) c.erase(v[i]);
    }
    for(int i = 0 ;i  < n ; i++){
        if(v[i] == 0 && (c.size() > 1 || !c.count(i+1))){
            b.insert(i); break;
        }
    }
    for(int i = n-1 ;i >= 0; i--){
        if(v[i] == 0 && (c.size() > 1 || !c.count(i+1))){
            b.insert(i); break;
        }
    }
    if(b.empty()) cout<<0<<ln;
    else cout<<*b.rbegin()-*b.begin()+1<<ln;
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