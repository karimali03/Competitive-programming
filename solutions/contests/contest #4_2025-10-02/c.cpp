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
struct compress {
    vector<int> org;
    map<int,int>mp;
    int sz;
    compress(vector<int> v){
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        for(int i = 0 ;i < (int)v.size() ; i++) mp[v[i]] = i;
        for(auto &[a,b] : mp) org.push_back(a);
        sz = v.size();
    }
    int idx(int val){
        return mp[val];
    }

    int val(int idx){
        return org[idx];
    }
};

int MSB(int x){
    ll msb = 0;
    while (x){
        x >>= 1;
        msb++;
    }
    return msb - 1;
}
void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    compress cm(v);
    vii x(cm.sz);
    f(i,0,n) x[cm.idx(v[i])].push_back(i);
    pair<int,int> res = {0,0};
    int val = v[0];
    int sh = 1;
    for(int i = 0 ; i < cm.sz ; i++){
        int mn = 0;
        vi pre(x[i].size());
        pre[0] = 1;
        int mx = 1;
        pair<int,int> rng = {x[i][0],x[i][0]};
        int ml = x[i][0];
        for(int j = 1 ;j  < (int)x[i].size() ; j++){
            pre[j] = pre[j-1] + (1-x[i][j]+x[i][j-1]+1);
            if(pre[j]-mn > mx){
                mx = pre[j]-mn;
                rng = {ml,x[i][j]};
            }
            if(pre[j]-1 < mn){
                mn = pre[j]-1;
                ml = x[i][j];
            }
        }
        if(mx > sh){
            sh = mx; res= rng;
            val = cm.val(i);
        }
        // 2^mx * v[cm.val(i)]
    }
    cout<<val<<" "<<res.first+1<<" "<<res.second+1<<ln;
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