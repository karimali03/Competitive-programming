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
    int n,y; cin>>n>>y;
    vi v(n); cin>>v;
    int mx = *max_element(all(v));
    vi pre(mx*2+4),cnt(mx*2+4);
    f(i,0,n) cnt[v[i]]++;
    for(int i = 1 ; i <= mx*2 ; i++) pre[i] = cnt[i] + pre[i-1];
    int res = - y * n;
    for(int c = 2 ; c <= mx*2 ; c++){
        int cur = 0;
      //  cout<<"c "<<c<<ln;
        for(int x = c ; x <= mx*2 ; x+=c){
            int sum = pre[x] - pre[x-c];
        //   cout<<x<<" "<<sum<<ln;
            cur += sum * (x/c);
            int diff = sum - cnt[x/c];
            if(diff > 0) cur -= y * diff;
        }
        res = max(res , cur);
    }
    cout<<res<<ln;
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