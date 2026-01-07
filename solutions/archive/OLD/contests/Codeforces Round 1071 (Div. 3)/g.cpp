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


map<pair<int,int>,int>mp;
int ask(int i,int j){
    if(i == j) return 0;
    if(i < j) swap(i,j);
    if(mp.count({i,j})) return mp[{i,j}];
    cout<<"? "<<i<<" "<<j<<endl;
    int ret; cin>>ret;
    return mp[{i,j}] = ret;
}

void solve(int test_case) {
    mp.clear();
    int n; cin>>n;
    vii res(n+1,vi(n+1));
    int c1 = 1;
    int mx = 0;
    for(int i = 2 ; i <= n*n ; i++){
        int x = ask(1,i);
        if(x > mx){
            mx = x;
            c1 = i;
        }
    }

    vi opt;
    for(int i = 1 ; i <= n*n ; i++){
        if(ask(c1,i) == n-1) opt.push_back(i);
    }
    int sz = opt.size();
    int c2 = opt[0];
    mx = 0;
    for(int i = 1 ; i < sz ; i++){
        int x = ask(opt[0],opt[i]);
        if(x >  mx){
            mx = x;
            c2 = opt[i]; 
        }
    }

    // c1  c2
    for(int i = 1 ; i <= n*n ; i++){
        int a = ask(c1,i);
        int b = ask(c2,i);
        int r = (a+b-(n-1))/2;
        int c = a - r;
        res[r][c] = i;
    }

    cout<<"!"<<endl;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cout<<res[i][j]<<" ";
        }
        cout<<endl;
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