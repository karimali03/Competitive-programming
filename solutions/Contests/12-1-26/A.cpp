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
    int sum = n*(n+1)/2;
    vii v(n,vi(n));
    vii op;
    for(int i = 0;i < n ; i++) op.push_back({1,i+1});
    for(int i =0 ;i < n ; i++) for(int j = 0;j < n;  j++) v[i][j] = j+1;
    int rem = n;
    for(int j = 0;j < n; j++){
        if((j+1)*n >= sum) break;
        op.push_back({2,j+1}); rem--;
        for(int i = 0; i < n ;i++) v[i][j] = i+1;
    }
    for(int i = n-1 ; i >= 0 && rem > 1;  i--){
        int cur = 0;
        int tag = sum - 1 + i+1;
        f(j,0,n) cur += v[j][i];
        if(tag > cur){
            op.push_back({2,i+1});
           f(j,0,n) v[j][i] = j+1;
            rem--;
        }
    }
    if(rem){
        op.push_back({1,1});
        f(i,0,n) v[0][i] = i+1;
    } 
    cout<<"--*-\n";
    f(i,0,n) cout<<v[i]<<ln;
    cout<<"----\n";

    int res = 0;
    f(i,0,n) f(j,0,n) res += v[i][j];
    cout<<res<<" ";
    cout<<op.size()<<ln;
    for(auto it : op){
        cout<<it[0]<<" "<<it[1]<<" ";
        f(i,1,n+1) cout<<i<<" ";
        cout<<ln;
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