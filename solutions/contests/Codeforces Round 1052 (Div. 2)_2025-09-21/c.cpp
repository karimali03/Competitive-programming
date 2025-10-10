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
    string s; cin>>s;
    if(count(all(s),'0') == n){
        YES;
        for(int i = n ; i >= 1 ; i--) cout<<i<<" ";
        cout<<ln;
        return;
    }
    for(int i = 0 ;i < n ; ){
        while (i < n && s[i] == '1') i++;
        int cnt = 0;
        while(i < n && s[i] == '0') cnt++,i++;
        if(cnt == 1){
            NO; return;
        }
    }
    YES;
    vi res(n);
    f(i,0,n) res[i]  =i+1;
    int prv = -1;
    for(int i = 0 ; i < n ; i++){
        if(s[i] == '1'){
            reverse(res.begin()+prv+1,res.begin()+i);
            prv = i;
        }
    }
    reverse(res.begin()+prv+1,res.end());
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