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
    vi v(n); cin>>v;
    vi suf(n),pre(n);
    suf[n-1] = v[n-1];
    for(int i = n-2 ; i >= 0 ; i--){
        suf[i] = min(suf[i+1] , v[i]); 
    }
    pre[0] = v[0];
    for(int i = 1 ; i < n ;i++) pre[i] = max(pre[i-1],v[i]);

    vi prv(n,-1),nxt(n,-1);
    int cur = 0;
    for(int i = 1 ; i < n ; i++){
        if(v[i] > v[cur]) cur = i;
        if(v[i] < v[cur]) prv[i] = cur;
    }
    auto calc = [&](int l,int r){
        int ans = -1;
        int base = v[l];
        while(l<=r){
            int mid = l + (r-l)/2;
            if(suf[mid] < base){
                ans = mid;
                l = mid+1;
            }else r = mid-1;
        }
        return ans == -1 ? -1 : ans;
    };
    for(int i = 0;i < n ; i++){
        nxt[i] = calc(i,n-1);
    }

    vi dp(n,-1);
    function<int(int)> rec = [&](int i) -> int{
        int &ret = dp[i];
        if(~ret) return ret;
        ret = v[i];
        if(prv[i] != -1) ret = max(rec(prv[i]),ret);
        if(nxt[i] != -1) ret = max(rec(nxt[i]),ret);
        return ret;
    };
    f(i,0,n) rec(i);
    cout<<dp<<ln;
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