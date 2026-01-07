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

const int N = 500005;
const int LOG = 20;
int jump[N][LOG]{};
void solve(int test_case) {
    int n,m; cin>>n>>m;
    for(int i = 0;i < n ; i++){
        int l,r; cin>>l>>r;
        jump[l][0] = max(jump[l][0] , r);
    }
    for(int i = 1 ; i < N ; i++){
        jump[i][0] = max(jump[i][0] , jump[i-1][0]);
    }
    for(int j = 1 ; j < LOG ; j++){
        for(int i = 0 ; i < N;  i++){
            jump[i][j] = jump[jump[i][j-1]][j-1];
        }
    }

    while(m--){
        int l,r; cin>>l>>r;
        int cur = l;
        int cnt = 0;
        for(int j = LOG-1 ; j >= 0 ; j--){
            if(jump[cur][j] < r) cur = jump[cur][j],cnt += (1<<j);
        }
        if(jump[cur][0] >= r) cout<<cnt+1<<ln;
        else NA;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}