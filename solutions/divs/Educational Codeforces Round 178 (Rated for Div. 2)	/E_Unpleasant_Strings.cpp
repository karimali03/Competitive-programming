#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

int dp[1000005];
int n,k;
vii idx(26);
int rec(int i){
    if(i >= n) return 0;
    int &ret = dp[i];
    if(~ret) return ret;
    ret = n;
    for(int c = 0 ; c <  k ; c++){
        if(idx[c].empty() || idx[c].back() <= i){
            ret = min(ret , 1ll);
            continue;
        }
        int nxt = idx[c][upper_bound(all(idx[c]),i)-idx[c].begin()];
        ret = min(ret , 1 + rec(nxt));
    }
    return ret;
}

void solve(int test_case){
    cin>>n>>k;
    memset(dp,-1,sizeof(dp));
    string s; cin>>s;
    f(i,0,n){
        idx[s[i]-'a'].push_back(i);
    }
    int q; cin>>q;
    while(q--){
        string x; cin>>x;
        int i = -1;
        int res=  -1;
        for(int j = 0 ; j  < x.size() && res == -1 ; j++){
            if(idx[x[j]-'a'].empty() || idx[x[j]-'a'].back() <= i){
                res = 0;
            }
            else{
             i = idx[x[j]-'a'][upper_bound(all(idx[x[j]-'a']),i)-idx[x[j]-'a'].begin()];
            }
        }

        if(res == 0) cout<<0<<ln;
        else cout<<rec(i)<<ln;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}