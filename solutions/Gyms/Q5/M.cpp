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
    vi a(n),b(n); cin>>a>>b;
    bool vld = true;
    for(int i = 0; i < n ; i++){
        for(int x = 0; x < 60 ; x++){
            int b1 = (a[i]>>x)&1;
            int b2 = (b[i]>>x)&1;
            if( !b1 && b2 ) {
                vld = false;
            }
        }
    }   
    if(!vld){
        NO; return;
    }
    vector<pair<int,int>>ops;
    vi vis(60);
    int base = (1ll << 60) - 1;
    for(int i = n-1 ; i >= 0 ; i--){
        int k = base;
        for(int x = 0;  x < 60 ; x++){
            int b1 = (a[i]>>x)&1;
            int b2 = (b[i]>>x)&1;
            if(vis[x]){
                if(b1 && !b2){
                    NO; return;
                }
            }
            if(b1 && b2){
                vis[x] = 1;
            }
            else if(b1 && !b2){
                k ^= (1ll << x);
            }
        }
        if(k != base) ops.push_back({k,i});
    }
    YES;
    cout<<ops.size()<<ln;
    for(auto &[l,r] : ops) cout<<r+1<<" "<<l<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}