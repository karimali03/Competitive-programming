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

int di[] = {0,1,-1,0};
int dj[] = {1,0,0,-1};
void solve(int test_case) {
    int n,m; cin>>n>>m;
    vii v(n,vi(m));
    for(int i = 0;i < n;  i++){
        for(int j=0;j<m;j++){
            char ch; cin>>ch;
            if(ch == 'A') v[i][j] = 0;
            else if(ch == 'B') v[i][j] = 1;
            else v[i][j] = 2;
        }
    }

    deque<array<int,4>>q;
    viii dist(n+1,vii(m+1,vi(4,-1)));
    q.push_back({0,0,0,0});
    auto calc = [&](int x,int y,int val) -> bool{
        if(x == y) return val == 0;
        if(y == 0) return (val == 1 && x == 1) || (val == 2 && x == 2);
        if(y == 1) return (val == 1 && x == 0) || (val == 2 && x == 3);
        if(y == 2) return (val == 1 && x == 3) || (val == 2 && x == 0);
        return (val == 1 && x == 2) || (val == 2 && x == 1);
    };
    while(!q.empty()){
        auto cur = q.front(); q.pop_front();
        int i = cur[0],j = cur[1];
        int cost = cur[3];
        int ch = cur[2];
        if(i < 0 || j < 0) continue;
        if(dist[i][j][ch] != -1) continue;
        dist[i][j][ch] = cost;
        if(i >= n || j >= m) continue;
        for(int dir = 0 ; dir < 4 ; dir++){
            if(ch+dir == 3) continue;
             if(calc(ch,dir,v[i][j])) q.push_front({i+di[dir],j+dj[dir],dir,cost});
             else q.push_back({i+di[dir],j+dj[dir],dir,cost+1});
        }
    }
    cout<<dist[n-1][m][0]<<ln;
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