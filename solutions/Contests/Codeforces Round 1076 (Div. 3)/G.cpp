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


int ask(int x,int y){
    cout<<"? "<<x+1<<" "<<y+1<<endl;
    int ret; cin>>ret;
    return ret;
}

void answer(int x){
    cout<<"! "<<x+1<<endl;
    return;
}

void solve(int test_case) {
    int n; cin>>n;
    vii g(n);
    for(int i = 1 ; i < n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vi ord;
    function<void(int,int)> dfs = [&](int x,int p){
        ord.push_back(x);
        for(auto it : g[x]) if(it != p){
            dfs(it,x);
        }
    };
    dfs(0,-1);
    for(int i = 1; i < n ; i+=2){
        if(ask(ord[i],ord[i-1])){
            if(ask(ord[i],ord[i])) answer(ord[i]);
            else answer(ord[i-1]);
            return;
        }
    }
    answer(ord.back());
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