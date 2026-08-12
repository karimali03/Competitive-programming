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


const int N = 1e6+5;
// largest prime factor
int lpf[N]{};
// ( N log(log(n) ) because we skip composites and only process primes
void LPF(){
    for(int i = 2 ; i < N ; i++){
        if(lpf[i]) continue;
        for(int j = i; j < N ; j += i) lpf[j] = i;
    }
}



void solve(int test_case) {
    int n,q; cin>>n>>q;
    LPF();
    vii g(n+1);
    for(int i = 2 ; i <= n ; i++){
        g[i / lpf[i]].push_back(i);
    }
    vi order;
    function<void(int)> dfs = [&](int x){
        order.push_back(x);
        for(auto &it : g[x]) dfs(it);
    };
    dfs(1);
    while(q--){
        int x; cin>>x;
        cout<<order[x-1]<<ln;
    }
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