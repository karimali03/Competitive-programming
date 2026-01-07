#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

int dx[]{1,-1,0,0};
int dy[]{0,0,1,-1};

void solve(int test_case){
    int n,m,k; cin>>n>>m>>k;
    queue<pair<int,int>>q;
    int vis[n][m]{};
    f(i,0,k){
        int x,y; cin>>x>>y; x--,y--;
        q.push({x,y});
        vis[x][y] = 1;
    }   
    int lvl = -1;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto [x,y] = q.front(); q.pop();
            for(int d = 0; d < 4 ; d++){
                int ni = dx[d] + x;
                int nj = dy[d] + y;
                if(ni >= 0 && nj >= 0 && ni < n && nj < m && !vis[ni][nj]){
                    q.push({ni,nj});
                    vis[ni][nj] = 1;
                }
            }
        }
        lvl++;
    }
    cout<<lvl<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}