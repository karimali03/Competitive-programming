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



const int N = 1'000'005;
const int M = 1'000'000'007;
int fact[N], inv_fact[N];

int fp(int x, int y) {
    int res = 1;
    while (y > 0) {
        if (y & 1) res = 1LL * res * x % M;
        x = 1LL * x * x % M;
        y >>= 1;
    }
    return res;
}

void INIT() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < N; i++) 
        fact[i] = 1LL * i * fact[i - 1] % M;
    for (int i = 1; i < N; i++) 
        inv_fact[i] = fp(fact[i], M - 2);
}

int nCr(int n, int k) {
    if (n < k || k < 0) return 0;
    return 1LL * fact[n] * inv_fact[k] % M * inv_fact[n - k] % M;
}


void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vi pre(n*3);
    auto add = [&](int l,int r){
        if(l >= n) return;
        r = min(r,n-1);
        pre[l]++; pre[r+1]--;
    };
    for(int i = 0;i < n; i++){
        add((i+1)*v[i],(i+1)*v[i]+i);
    }
    for(int i = 1 ; i < n ; i++){
        pre[i] += pre[i-1];
    } 
    for(int i = n ; i < 3*n ; i++){
        pre[i] = 1;
    }
    for(int i = 0;i < 3*n ; i++){
        if(pre[i]) pre[i] = 1;
        if(i) pre[i] += pre[i-1];
    }
    
    auto get = [&](int l,int r) -> pair<int,int>{
        if(l > r) return {0,0};
        int bad = pre[r] - (l ? pre[l-1] : 0);
        int good = r-l+1 - bad;
        return {good,bad};
    };

    auto prefix = [&](int len,int x){
        int res = 0;
        for(int i = 1 ; i <= x ; i++){
            res += nCr(len,i);
            res %= M;
        }
        return res;
    };
    int idx = 0;
    int res = 1;
    int prv = -1;
    int len = 0;
    int val = 0;
    for(int i = 1;i < n; i++){
        int blk = idx / i;
        int st = blk * i;
        if(prv != -1 && prv+i-1 > st){
            cout<<"----"<<i<<" "<<prv<<" "<<val<<ln;
            res = res * fp(val,M-2) % M;
            int cur = get(prv,st-1).first;
            res = res * fp(2,cur) % M;
            cout<<"--"<<cur<<" "<<res<<ln;
        }
        while(true){
            auto [x,y] = get(st,st+i-1);
            cout<<i<<" "<<x<<" "<<y<<" "<<st<<" "<<st+i-1<<ln;
            if(x == 0){
                if(st >= n) idx = st;
                else  idx = st+i; 
                break;
            }
            prv = st; len = i;
            val = prefix(x,x);
            cout<<i<<" "<<st<<" "<<st+i-1<<" -- "<<val<<" "<<res<<ln;
            res = res * val % M;
            st += i;
        }
    }
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    INIT();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}