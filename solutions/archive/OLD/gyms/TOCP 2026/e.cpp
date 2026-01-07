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

const int N = 505;
int v[N][N]{};
int vis[N][N]{};
int cnt = 0;
int n,m,k;
int cor[4]; 
int dx[] = {-1,1,0,0};
int dy[] = {0,0,1,-1};

bool vld(int x,int y){
    return x > 0 && y > 0 && x <= n && y <= m; 
}

bool in(int x,int y){
    return x >= cor[0] && x <= cor[2] && y >= cor[1] && y <= cor[3];
}
bool can(int mx){
    cnt++;
    queue<pair<int,int>>q;
    q.push({cor[0],cor[1]});
    vis[cor[0]][cor[1]] = cnt;
    int inside = 0;
    int outside = 0;
    while(!q.empty()){
        auto [x,y] = q.front(); q.pop();
        if(in(x,y)) inside += (v[x][y] > 0);
        else outside += (v[x][y] == 0);
        for(int d = 0; d < 4 ; d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(vld(nx,ny) && vis[nx][ny] != cnt && v[nx][ny] <= mx){
                vis[nx][ny] = cnt;
                q.push({nx,ny});
            }
        }
    }
    return outside >= inside;
}
void solve(int test_case) {
    cin>>n>>m>>k;
    int l = 0 , r = k;
    for(int i = 1 ; i <= k ; i++){
        int x,y; cin>>x>>y;
        v[x][y] = i;
    }
    for(int i = 0; i < 4 ; i++) cin>>cor[i];
    f(i,1,n+1) f(j,1,m+1) if(in(i,j)) l = max(l , v[i][j]);

    int ans = -1;
    while(l<=r){
        int mid = (l+r)/2;
        if(can(mid)){
            ans = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    cout<<ans<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}