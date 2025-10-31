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
    vii g(n);
    for(int i = 1 ; i < n; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    auto bfs = [&](int x) -> vi{
        queue<int>q;
        vi d(n,-1);
        d[x] = 0; q.push(x);
        while(!q.empty()){
            auto cur = q.front(); q.pop();
            for(auto x : g[cur]) if(d[x] == -1){
                d[x] = 1 + d[cur];
                q.push(x);
            }
        }
        return d;
    };
    auto d1 = bfs(0);
    auto d2 =  bfs(n-1);
    // nodes on path
    // nodes not on path
    vi a,b;
    for(int i = 0; i < n ; i++){
        if(d1[i] + d2[i] == d1[n-1]) a.push_back(i);
        else b.push_back(i);
    }
    sort(all(b),[&](int x,int y){
        return d1[x] > d1[y];
    });
    vii op;
    int k = 0;
    for(auto it : b){
        op.push_back({1,1}); k++;
        if(d1[it]%2 == k%2) op.push_back({1,1}),k++;
        op.push_back({2,it+1});
    }
    sort(all(a),[&](int x,int y){
        return d1[x] < d1[y];
    });
    for(auto it : a){
        if(it == n-1) break;
        op.push_back({1,1}); k++;
        if(d1[it]%2 == k%2) op.push_back({1,1}),k++;
        op.push_back({2,it+1});
    }
    cout<<op.size()<<ln;
    for(auto it : op){
        if(it[0] ==1) cout<<1<<ln;
        else cout<<it[0]<<" "<<it[1]<<ln;
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