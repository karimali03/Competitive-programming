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


map<int,int>v;
int sz;
vi row;
int calc(){
    set<int>st;
    for(int i = 0;i < sz ; i++){
        if(v[row[i]]) continue;
        int y = row[i];
        set<int>xx;
        while(y <= row.back()){
            if(!v[y]) xx.insert(y);
            v[y] = 1;
            y *= row[i];
        }
        st.insert(calc());
        for(auto &it : xx) v[it] = 0;
    }
    int mex = 0;
    while(st.count(mex)) mex++;
    return mex;
}
int solve(int n) {
    vi vis(n+1);
    vii opt;
    for(int i = 2 ; i <= n ; i++){
        if(vis[i]) continue;
        int x = i;
        vi cur;
        while(x <= n){
            vis[x] = 1;
            cur.push_back(x);
            x*=i;
        } 
        opt.push_back(cur);
    }
    int xr = 0;
    for(auto &it : opt){
        row = it;
        sz = row.size();
        int ans = calc();
        xr ^= ans;
    }

    if(xr) return 0;
    return 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        if(solve(i)) cout<<i<<ln;
    }

    return 0;
}