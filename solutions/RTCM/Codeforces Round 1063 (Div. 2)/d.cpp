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

int ask(int l,int r){
    cout<<"? "<<l<<" "<<r<<endl;
    int ret; cin>>ret;
    return ret;
}

void answer(int res){
    cout<<"! "<<res<<endl;
}
void solve(int test_case) {
    int n,q; cin>>n>>q;
    vector<int> l(q),r(q);
    f(i,0,q) cin>>l[i]>>r[i];
    int mx_q = max(300 , ((n+1)/2)+2);
    if(q <= mx_q){
        int res = 0;
        for(int i = 0; i < q; i++) res = max(res , ask(l[i],r[i]));
        answer(res); return;
    }
    vector<int> mn(n+1, 1e9), mx(n+1, -1);
    for (int i = 0; i < q; i++) {
        mx[l[i]] = max(mx[l[i]], r[i]);
        mn[r[i]] = min(mn[r[i]], l[i]);
    }
    if(ask(1,n/2)){
        int res = 0;
        for(int i = 1 ; i <= n/2 ; i++){
            if(mx[i] == -1) continue;
            res = max(res , ask(i,mx[i]));
        }
        answer(res);
    }else{
        int res = 0;
        for(int i = n/2+1 ; i <= n ; i++){
            if(mn[i] == 1e9) continue;
            res = max(res , ask(mn[i],i));
        }
        answer(res);
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