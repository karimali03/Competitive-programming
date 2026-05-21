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

#define loop(u,e,v) for (int e = head[u], v; ~e && (v = to[e], 1); e = nxt[e])
const int N = 1000005;
const int M = 2000005;
int head[N],to[M],nxt[M],ne;
void init(int n){
    ne = 0;
    memset(head,-1,n*sizeof(head[0]));
}
void add(int u,int v,int w = 0){
    to[ne] = v;
    nxt[ne] = head[u];
    head[u] = ne++;
}


void solve(int test_case) {
    int n; cin>>n;
    init(n);
    f(i,0,n-1){
        int x,y; cin>>x>>y; x--,y--;
        add(x,y); add(y,x);
    }    
    vi a(n),b(n); cin>>a>>b;
    vi res;
    function<void(int,int,int,int,int)> dfs = [&](int x,int p,int ev,int od,int cur){
        int val = cur ? a[x]^ev : a[x]^od;
        if(val != b[x]){
            res.push_back(x+1);
            if(cur) ev^=1;
            else od^=1;
        }
        loop(x,e,v){
            if(v == p) continue;
            dfs(v,x,ev,od,cur^1);
        }
    };
    dfs(0,-1,0,0,0);
    cout<<res.size()<<ln;
    cout<<res;
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