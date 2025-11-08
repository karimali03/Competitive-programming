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
    int n,k,x; cin>>n>>k>>x;
    vi v(n); cin>>v;
    sort(all(v));
    auto calc = [&](int l,int r){
        return l > r ? 0 : r-l+1;
    };
    auto can = [&](int mx) -> bool{
        int prv = -1;
        int cnt = k;
        for(int i = 0;i <= n ;i++){
            if(i == n) cnt -= calc(prv+mx,x);
            else if(i) cnt -= calc(prv+mx,v[i]-mx);
            else cnt -= calc(0,v[i]-mx);
            prv = v[i];
        }
        return cnt <= 0;
    };
    int ans = 0;
    int l = 1 , r = 1e9;
    while(l<=r){
        int mid = l + (r-l)/2;
        if(can(mid)){
            ans = mid;
            l = mid+1;
        }else r = mid-1;
    }
    int mx = ans;
    int prv = -1;
    int cnt = k;
    if(ans == 0){
        for(int i = 0 ; i < k;  i++) cout<<i<<" ";
        cout<<ln; return;
    }
    for(int i = 0;i <= n ;i++){
        pair<int,int>inv;
        if(i == n) inv =  {prv+mx,x};
        else if(i) inv =  {prv+mx,v[i]-mx};
        else inv = {0,v[i]-mx};
        prv = v[i];
        int it = calc(inv.first,inv.second);
        for(int a = 0; a < min(cnt,it) ; a++){
            cout<<inv.first+a<<" ";
        }
        cnt -= it;
        if(cnt <= 0) break;
    }
    cout<<ln;
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