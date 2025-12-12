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
    int n,m; cin>>n>>m;
    vii v(n,vi(m));
    for(int i = 0;i < n ; i++){
        for(int j = 0;j < m ; j++){
            cin>>v[i][j]; v[i][j]--;
        }
    }
    vi base(m);
    iota(all(base),0);
    if(n < 500){
        vii ans(n,vi(n));
        for(int st = 0; st < n ; st++){
            vi cur = base;
            for(int en = st ; en < n ; en++){
                int sum = 0;
                for(int i = 0;i < m ; i++){
                    cur[i] = v[en][cur[i]];
                    sum += (cur[i]+1) * (i+1);
                }
                ans[st][en] = sum;
            }
        }

        int q; cin>>q;
        while(q--){
            int l,r; cin>>l>>r; l--,r--;
            cout<<ans[l][r]<<ln;
        }
    }else{
        viii jump(20,vii(n+1,vi(m)));
        for(int i = 0;i < n ; i++){
            for(int j = 0;j < m ; j++) jump[0][i][j] = v[i][j];
        }
        for(int lg = 1 ; lg < 20 ; lg++){
            for(int i = 0; i + (1 << lg) <= n ; i++){
                for(int j = 0;j < m ; j++){
                    int mid = jump[lg-1][i][j];
                    int final_val = jump[lg-1][i + (1 << (lg-1))][mid];
                    jump[lg][i][j] = final_val;
                }
            }
        }
        
        int q; cin>>q;
        while(q--){
            int l,r; cin>>l>>r; l--,r--;
            int k = r - l + 1;
            vi cur = base;
            int idx = l;
            for(int lg = 0;lg < 20 ; lg++){
                if((k>>lg)&1){
                    for(int x = 0; x < m ; x++){
                        cur[x] = jump[lg][idx][cur[x]];
                    }
                    idx += (1 << lg);
                }
            }
            int sum = 0;
            for(int i = 0;i < m ; i++) sum += (i+1)*(cur[i]+1);
            cout<<sum<<ln;
        }


    }

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