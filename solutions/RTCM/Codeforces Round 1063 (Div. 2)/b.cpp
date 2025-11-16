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
    string s; cin>>s;
    for(int i = 0; i < n ; i++){
        if(s[i] == '1' && (v[i] == 1 || v[i] == n)){
            NA; return;
        }
    }   
    if(s[0] == '1' || s[n-1] == '1'){
        NA; return;
    }
    pair<int,int> idx;
    for(int i = 0; i < n ; i++){
        if(v[i] == 1) idx.first = i;
        if(v[i] == n) idx.second = i;
    }
    
    cout<<5<<ln;
    cout<<min(idx.first,idx.second)+1<<" "<<max(idx.first,idx.second)+1<<ln;
    cout<<min(0ll,idx.first)+1<<" "<<max(0ll,idx.first)+1<<ln;
    cout<<min(n-1,idx.first)+1<<" "<<max(n-1,idx.first)+1<<ln;
    cout<<min(0ll,idx.second)+1<<" "<<max(0ll,idx.second)+1<<ln;
    cout<<min(n-1,idx.second)+1<<" "<<max(n-1,idx.second)+1<<ln;
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