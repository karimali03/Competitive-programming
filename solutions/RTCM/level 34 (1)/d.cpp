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
    if(n == 1){
        if(k == 1){
            YES; cout<<"0\n";
        }
        else NO;
        return;
    }
    if(n == 2){
        if(k == 1){
            YES; cout<<"1\n1 2\n";
        }
        else NO;
        return;
    }
    if(n < k*2-1){
        NO; return;
    }
    vii g;
    g.push_back({0,1});
    vi lst;
    int cur = 1;
    for(int i = 2 ; i <= k ; i++){
        int rem = i-1;
        int use = min(n - cur - 1, i - 1);
        int x = cur;
        for(int a = 0; a < use ; a++){
            g.push_back({x,++cur});
            if(a != 0) lst.push_back(cur);
        }
        for(int a = 0 ; a < rem - use ; a++)  g.push_back({x,lst[a]});
    }
    for(int x = cur+1 ; x < n ; x++) g.push_back({x-1,x});
    if(k == 1) g.push_back({0,n-1});
    YES;
    cout<<g.size()<<ln;
    for(auto &it : g) cout<<it[0]+1<<" "<<it[1]+1<<ln;
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