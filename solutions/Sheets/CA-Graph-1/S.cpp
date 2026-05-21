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
    int n,m,x; cin>>n>>m>>x;
    vi st(x); cin>>st;
    int ev = 0 , od=0;
    for(auto &it : st){
        if(it&1) od += it;
        else ev += it;
    }
    vii g(n);
    f(i,0,m){
        int x,y; cin>>x>>y;x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }   
    queue<int>q; q.push(0);
    vi dist(n,-1);
    dist[0] = 0;
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(auto &it : g[cur]){
            if(dist[it] != -1) continue;
            dist[it] = 1 + dist[cur];
            q.push(it);
        }
    }
    string res(n,'0');
    for(int i = 0;i  < n ; i++){
        if(dist[i]&1){
            int x = max(0ll , dist[i] - ev);
            if(od && od >= x) res[i] = '1';
        }else{
            
        }

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