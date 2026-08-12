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
    int n; cin>> n;
    vi a(n); cin>>a;
    string s; cin>>s;
    if(count(all(s),'=') == n-1){
        int sum = 0;
        for(auto &it : a) sum += it;
        cout<<sum<<ln;
        for(int i = 0;i < n ; i++) cout<<"1 ";
        cout<<ln;        
        return;
    }
    int prv = 0;
    vii g(n);
    for(int i = 1 ; i < n ; i++){
        if(s[i-1] == '=') continue;
        if(s[i-1] == '>'){
            g[i].push_back(prv);
        }else g[prv].push_back(i);
        prv = i;
    }
    vi res(n);
    vi in(n);
    for(int i = 0;i < n ; i++){
        for(auto &it : g[i]) in[it]++;
    }
    queue<int>q;
    for(int i = 0;i < n ; i++){
        if(g[i].empty()) continue;
        if(in[i] == 0) q.push(i);
    }

    int val = 1;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto it = q.front(); q.pop();
            res[it] = val;
            for(auto &x : g[it]){
                if(--in[x] == 0){
                    q.push(x);
                }
            }
        }
        val++;
    }
    for(int i = 1 ;i  < n ;i++){
        if(s[i-1] == '=') res[i] = res[i-1];
    }
    int sum = 0;
    for(int i = 0;i  <n ; i++) sum += (a[i] * res[i]);
    cout<<sum<<ln;
    cout<<res<<ln;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}