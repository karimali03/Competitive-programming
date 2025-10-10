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

// get the most significant bit
int MSB(int x){
    ll msb = 0;
    while (x){
        x >>= 1;
        msb++;
    }
    return msb - 1;
}
void solve(int test_case) {
    int l,r; cin>>l>>r;
    if(l == 0 && r == 0){
        cout<<0<<ln; 
        cout<<0<<ln;
        return;
    }
    int n = r - l + 1;
    int res = 0;
    vi ans(n);
    function<void(int,int)> calc = [&](int a,int b){
        if(a > b) return;
        if(a == b){
            res += a; ans[a-l] = a; return;
        }
        int x = MSB(b);
        int nxt = (1ll<<x);
        int prv = (1ll<<x)-1;
        int aa = a , bb = b;
        while(MSB(aa) == MSB(bb)){
            aa -= (1ll<<MSB(aa));
            bb -= (1ll<<MSB(bb));
            nxt += (1ll<<MSB(bb));
            prv = nxt - 1;
        } 
        for(int i = nxt ; i <= b && prv >= a; i++){
            res += (i | prv) * 2; 
            ans[i-l]  = prv; ans[prv-l] = i;
            nxt++,prv--;
        }
        calc(a,prv);   calc(nxt,b);
    };
    calc(l,r);
    cout<<res<<ln;
    cout<<ans<<ln;
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