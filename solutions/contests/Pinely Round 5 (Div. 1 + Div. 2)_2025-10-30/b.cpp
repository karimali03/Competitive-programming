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

int n;
bool vld(int x,int y){
    return x >= 0 && y >= 0 && x < n && y < n;
}
vector<vector<pair<int,int>>> d = {
    {{1,0},{0,1}},
    {{1,0},{0,-1}},
    {{-1,0},{0,1}},
    {{-1,0},{0,-1}},
    {{0,1},{1,0}},
    {{0,1},{-1,0}},
    {{0,-1},{1,0}},  
    {{0,-1},{-1,0}}
};

int res = 0;
void calc(vii &v,int x,int y,int ch,int ty){
    if(!vld(x,y)) return;
    if(v[x][y] == 0) res++;
    calc(v, x + d[ch][ty].first , y + d[ch][ty].second , ch , 1 - ty);
}
void calc2(vii &v,int x,int y,int ch,int ty){
    if(!vld(x,y)) return;
    if(v[x][y] == 0) res++;
    calc2(v, x - d[ch][ty].first , y - d[ch][ty].second , ch , 1 - ty);
}
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};
void dfs(int r, int c, const vii& v, vii& vis) {
    if (!vld(r, c) || vis[r][c] || v[r][c] == 1) {
        return;
    }
    vis[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        dfs(r + dr[i], c + dc[i], v, vis);
    }
}
 
int count_components(const vii& v) {
    vii vis(n, vi(n, 0));
    int components = 0;
    int bl = 0;
    
    f(i, 0, n) {
        f(j, 0, n) {
            if (v[i][j] == 0) {
                bl++;
                if (!vis[i][j]) {
                    dfs(i, j, v, vis);
                    components++;
                }
            }
        }
    }
    
    return components;
}
bool chk(const vii& v) {
    f(i,0,n) if(count(all(v[i]),0) > 2) return false; 
    f(j,0,n){
        int c = 0;
        f(i,0,n) if(!v[i][j]) c++;
        if(c>2) return false;
    }
    return true;
}
void solve(int test_case) {
    cin>>n;
    vii v(n,vi(n));
    int cnt = 0;
    f(i,0,n) f(j,0,n){
        char ch; cin>>ch;
        if(ch == '.') v[i][j] = 1;
        else v[i][j] = 0,cnt++;
    }
    if(cnt == 0){
        YES; return;
    }
    if(!chk(v)){
        NO; return;
    }

    if(count_components(v) == 1){
        YES; return;
    }
    pair<int,int>x = {-1,-1};
    for(int i = 0 ; i < n ; i++){
        for(int j =0 ;j < n ; j++){
            if(!v[i][j]){
                x = {i,j};
                goto xx;
            } 
        }
    }
    xx:
    for(int i = 0;i < 8 ; i++){
        res = 0;
        calc(v,x.first,x.second,i,0);
        calc2(v,x.first,x.second,i,1);
        if(res-1 == cnt){
            YES; return;
        }
    }
    NO;


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