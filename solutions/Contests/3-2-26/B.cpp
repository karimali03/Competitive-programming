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


int di[] = {1,-1,0,0};
int dj[] = {0,0,1,-1};
void solve(int test_case) {
    int n,m; cin>>n>>m;
    vii v(n,vi(m));
    f(i,0,n)f(j,0,m){
        char x; cin>>x;
        if(x == '#') v[i][j] = 1;
        else v[i][j] = 0;
    }
    int comp = 2;
    vi cnt(n*m+5);
    function<void(int,int)> dfs = [&](int x,int y){
        v[x][y] = comp;
        cnt[comp]++;
        for(int d = 0 ; d < 4 ; d++){
            int ni = x + di[d];
            int nj = y + dj[d];
            if(ni >= 0 && nj >= 0 && ni < n && nj < m && v[ni][nj] == 1)
            dfs(ni,nj);
        }
    };
    f(i,0,n) f(j,0,m) if(v[i][j] == 1){
        dfs(i,j); comp++;
    }
    int mx = 0;
    set<int>st;
    int cur = 0;

    auto add = [&](int i,int j){
        if(i < 0 || i == n || v[i][j] == 0) return;
        if(!st.count(v[i][j])){
            cur += cnt[v[i][j]];
            st.insert(v[i][j]);
        }
    };
    auto add2 = [&](int i,int j){
        if(j < 0 || j == m || v[i][j] == 0) return;
        if(!st.count(v[i][j])){
            cur += cnt[v[i][j]];
            st.insert(v[i][j]);
        }
    };
    for(int i = 0;i < n ; i++){
        for(int j = 0;j < m ; j++){
            if(v[i][j] == 0){
                cur++;
                add(i-1,j); add(i+1,j);
            }
            else if(!st.count(v[i][j])){
                cur += cnt[v[i][j]];
                st.insert(v[i][j]);
            }
        }
       
        mx = max(mx , cur);
        cur = 0;
        st.clear();
    }
    for(int j = 0 ;j < m ; j++){
        for(int i = 0;i < n ; i++){
            if(v[i][j] == 0){
                cur++;
                add2(i,j-1); add2(i,j+1);
            }
            else if(!st.count(v[i][j])){
                cur += cnt[v[i][j]];
                st.insert(v[i][j]);
            }
            
        }
      
        mx = max(mx , cur);
        cur = 0;
        st.clear();
    }

    cout<<mx<<ln;

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