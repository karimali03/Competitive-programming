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


// const int N = 21;
// int dp[1<<N];
// vector<pair<int,int>> x;
// int rec(int mask){
//     if(mask == 0) return 0;
//     int &ret = dp[mask];
//     if(~ret) return ret;
//     ret = 0;
//     vi cnt(7);
//     for(int j = 0 ; j < N ; j++){
//         if(!(mask>>j)&1) continue;
//         cnt[x[j].first]++;
//         if(x[j].first != x[j].second) cnt[x[j].second]++;
//         ret += rec(mask ^ j);
//     }
//     ret += (count(all(cnt),1) <=2);
//     return ret;
// }
void solve(int test_case) {
   
    // map<pair<int,int>,int>idx;
    // int cnt = 0;
    // for(int i = 1 ; i <= 6 ; i++){
    //     for(int j = i ; j <= 6; j++){
    //         x.push_back({i,j});
    //         idx[x.back()] = cnt++;
    //     }
    // }
    
    int n; cin>>n;
    vi l(n),r(n);
    f(i,0,n){
        cin>>l[i]>>r[i];
    }
    int ans = 0;
    for(int i = 1 ; i < (1<<n) ; i++){
        vi cnt(7);
        for(int j = 0 ; j < n; j++){
            if(!((i>>j)&1)) continue;
            cnt[l[j]]++;
            if(l[j] != r[j]) cnt[r[j]]++;
        }
        int od = 0;
        for(int x = 0 ; x < 7 ; x++) if(cnt[x]&1) od++;
        ans += ( od <= 2);
    }
    cout<<ans<<ln;
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