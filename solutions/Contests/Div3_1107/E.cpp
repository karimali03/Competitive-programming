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


vector<int> multiply(vector<int> A,vector<int> B,int limit){
    int m = A.size();
    int n = B.size();
    int sz = min(n + m - 1 , limit +1);
    vector<int> prod(sz, 0);
    for(int i = 0; i < min(m,sz) ; i++){
        for(int j = 0;j < n ; j++){
            if(i+j > limit) break;
            prod[i+j] += A[i] * B[j];
        }
    }
    return prod;
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vii g(n);
    for(int i = 1 ; i< n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }   
    int res = 0;
    vi sz(n);
    function<void(int,int)> dfs = [&](int x,int p){
        sz[x] = 1;
        vector<int>ch;
        for(auto &it : g[x]) if(it != p){
            dfs(it,x);
            sz[x] += sz[it];
            ch.push_back(sz[it]);
        }
        if(n - sz[x]  > 0) ch.push_back(n - sz[x]);
        int sq = sqrt(v[x]);
        if((sq*sq) != v[x]) return;
        int sum = 0,pairs=0,triples=0;
        for(auto &it : ch){
            triples += it * pairs;
            pairs += it * sum;
            sum += it;
        }
        res += (pairs + triples);
    };
    dfs(0,-1);
    cout<<res <<ln;
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