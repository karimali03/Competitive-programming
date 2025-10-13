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
    vii adj(n);
    for(int i = 1 ; i < n  ; i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y); adj[y].push_back(x);
    }
    string s; cin>>s;
    int leaf[2]{};
    int root = (s[0] == '?' ? -1 : s[0]-'0');
    int mid = 0;
    int le = 0;
    function<void(int,int)> rec = [&](int x,int y)-> void{
        int cnt = 0;
        for(auto it:  adj[x]){
            if(it == y) continue;
            rec(it,x); cnt++;
        }
        if(x != 0 && !cnt && s[x] != '?') leaf[s[x]-'0']++;
        if(x != 0 && cnt && s[x] == '?') mid++;
        if(x != 0 && !cnt && s[x] == '?') le++;
    };
    rec(0,-1);
    int res = 0;
    if(root == -1){
        if(leaf[0] != leaf[1]) res = max(leaf[0],leaf[1]) + le/2;
        else if(mid&1) res = leaf[0] + (le+1)/2;
        else res = leaf[0] + le/2;
    }else res = leaf[1-root] + (le+1)/2;
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