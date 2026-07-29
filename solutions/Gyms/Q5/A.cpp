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



mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> dist(1, (1ll<<29)-1);


void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    for(int i = 0; i <  m ; i++){
        int l,r; cin>>l>>r;
    }   
    vi res(k);
    set<int>st;
    auto get = [&](){
        int cur = dist(rng);
        while(st.count(cur)){
            cur = dist(rng);
        }
        st.insert(cur);
        return cur;
    };
    int xr = 0;
    for(int i = 0; i < k-1 ; i++){
        int cur = get();
        xr ^= cur;
        res[i] = cur;
    }
    while(xr == 0){
        xr ^= res[k-2]; st.erase(res[k-2]);
        int cur = get();
        res[k-2] = cur;
        xr ^= cur;
    }
    res[k-1] = xr;
    for(int i = 0 ;i < n ; i++){
        cout<<res[i%k]<<" ";
    }
    cout<<ln;
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