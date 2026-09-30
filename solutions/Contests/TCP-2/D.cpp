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


// 1-indexed
// range update - point query
struct BIT {
    int n;
    vector<long long> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void add(int i, long long val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    long long sum(int i) {
        long long res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

    // add val to all a[l..r]
    void range_add(int l, int r, long long val) {
        if(l > r) return;
        add(l, val);
        if (r + 1 <= n)
            add(r + 1, -val);
    }

    // get a[i]
    long long point_query(int i) {
        return sum(i);
    }
};

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vi base = v;
    BIT st(n);
    auto apply = [&](int i){
        int l = v[i-1]%2;
        int r = v[i+1]%2;
        if(l == r){
            int nv = v[i-1] + v[i+1] - v[i];
            if(nv < v[i]){
                int diff = nv - v[i];
                st.range_add(i+2,n,diff);
                v[i] = nv;
            }
        }
    };
    for(int i = n-2 ; i >= 1 ; i--){
        apply(i);
    }
    for(int i = 1 ;i  < n-1 ; i++) cout<<st.point_query(i+1)+base[i]<<" ";
    cout<<ln;
    cout<<v[0]<<" ";
    for(int i = 1 ;i < n-1 ; i++){
        int l = v[i-1]%2; int r = v[i+1]%2;
        int val = st.point_query(i+1);
        if(l == r){
            cout<<min(val,base[i])<<" ";
        }else cout<<base[i]<<" ";
    }
    cout<<v[n-1]<<ln;
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