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

int c = 0;
pair<int,int> ask(int l,int r){
    c+=2;
    assert(c <= 40);
    cout<<"1 "<<l<<" "<<r<<endl;
    int s1 = 0; cin>>s1;
    cout<<"2 "<<l<<" "<<r<<endl;
    int s2 = 0; cin>>s2;
    return {s1,s2};
}
void solve(int test_case) {
    c = 0;
    int n; cin>>n;
    // vector<pair<int,int>>rngs;
    // function<void(int,int,pair<int,int>)> rec = [&](int l,int r,pair<int,int>s){
    //     int diff = abs(s.first-s.second);
    //     if(diff == 0) return;
    //     if(diff == r-l+1){
    //         rngs.push_back({l,r});
    //         return;
    //     }
    //     int m = (l+r)/2;
    //     auto a = ask(l,m);
    //     pair<int,int> b = {s.first-a.first,s.second-a.second};
    //     rec(l,m,a);
    //     rec(m+1,r,b);
    // };
    // auto cur = ask(1,n);
    // rec(1,n,cur);
    // auto [L,R] = rngs[0];
    // for(auto &[l,r] : rngs){
    //     L = min(L,l);
    //     R = max(r,R);
    // }
    // cout<<"! "<<L<<" "<<R<<endl;
    auto cur = ask(1,n);
    int len = cur.second-cur.first;
    int l = 1 , r = n;
    int ans = 1;
    while(l <= r){
        int m = (l+r)/2;
        auto x = ask(1,m);
        if(x.second-x.first == 0){
            l = m + 1;
        }else{
            r = m - 1;
            ans = m;
        }
    }
    cout<<"! "<<ans<<" "<<ans+len-1<<endl;
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