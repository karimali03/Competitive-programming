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

bool chk(ll x,ll y,ll cx,ll cy,ll r){
    ll r2 = r*r;
    ll d  = (x-cx)*(x-cx) + (y-cy)*(y-cy);
    if(d <= r2) return true;
    return false;
}

ll dist(ll x1,ll y1,ll x2,ll y2){
    ll ret = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    return ret;
}
void solve(int test_case) {
    int n; cin>>n;
    pair<int,int> P; 
    cin>>P.first>>P.second;
    int mn = 1e7;
    int idx = 0;
    vector<array<int,3>>c(n);
    for(int i = 0;i < n ; i++){
        for(int j=0;j<3;j++) cin>>c[i][j];
        if(c[i][2] < mn){
            mn = c[i][2];
            idx = i;
        }
    }
    ll prd = (ll)n * (ll)mn * (ll)mn;
    ll res = 1e18;
    ll b = 1;
    if(prd > 1e7){
        b = (prd+10000000-1) / 10000000;
        b = (b+1)/2;
        b = (2*mn) / b ;
    }
        int rd = c[idx][2];
        int lx = c[idx][0] - rd;
        int ly = c[idx][1] - rd;
        int rx = c[idx][0] + rd;
        int ry = c[idx][1] + rd;
        for(int l = lx ; l <= rx ; l+=b){
            for(int r = ly ; r <= ry ; r+=b){
                bool vld = true;
                for(int i = 0;i < n && vld ; i++){
                    if(!chk(l,r,c[i][0],c[i][1],c[i][2])) vld = false;
                }
                if(vld){
                    res = min(res , dist(P.first,P.second,l,r));
                }
            }
        }

    ld ret = sqrtl(res);
    cout<<fixed<<setprecision(7)<<ret<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}