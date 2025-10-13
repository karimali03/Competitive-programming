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
    int n,k; cin>>n>>k;
    if(k == n*n-1){
        NO; return;
    }
    vec<vec<char>>v(n,vec<char>(n,'.'));
    for(int i = 0 ; i < n && k ; i++){
        for(int j = 0 ;j  < n && k ; j++){
            v[i][j] = 'L'; k--;
        }
    }
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ;j  < n ; j++){
            if(v[i][j] != 'L'){
                if(n - j - 1){
                    v[i][j] = 'R';
                    for(int x = j+1 ; x < n; x++) v[i][x] = 'L';
                    goto xx;
                }else{
                    v[i][j] = 'D'; goto xx;
                }
            }
        }
    }
    xx:
    for(int i = 0 ; i < n; i++){
        if(v[i][0] == 'L') continue;
        v[i][0] = 'R';
        for(int j = 1 ;j  < n ; j++) v[i][j] = 'L';
    }
    YES;
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ;j  < n ; j++) cout<<v[i][j];
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