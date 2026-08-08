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
    map<int,vi>mp;
    for(int  i = 0;i < n ; i++) mp[v[i]].push_back(i);
    vi res(n);
    if(!mp.count(0)){
        NA; return;
    }
    vector<int>X;
    for(auto [a,b] : mp){
        X.push_back(a);
    }
    int sum = 0;
    vi back;
    for(int i = 1;i < (int)X.size() ; i++){
        int cnt = mp[X[i-1]].size();
        int rem = X[i] - sum;
        if(rem <= 0 || (rem%cnt)){
            NA; return;
        }
        if(!back.empty() && back.back() >= (rem/cnt)){
            NA; return;
        }
        for(auto &it : mp[X[i-1]]){
            res[it] = rem / cnt;
        }
        back.push_back(rem/cnt);
        sum += rem;
    }
    int mx = *max_element(all(res));
    for(int i  =0;i < n ; i++){
        if(res[i]) cout<<res[i]<<" ";
        else cout<<mx+1<<" ";
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