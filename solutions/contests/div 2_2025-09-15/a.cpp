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
    vi v(n); cin>>v;
    vi pre(n);
    pre[0] = v[0];
    for(int i =1;  i < n ; i++) pre[i] = v[i] + pre[i-1];
    auto calc = [&](int l,int r) -> int{
        return pre[r] - (l ? pre[l-1] : 0);
    };
    for(int l = 0 ; l < n-1 ; l++){
        for(int r = l+1 ; r < n-1 ; r++){
            int a = calc(0,l) % 3;
            int b = calc(l+1,r) % 3;
            int c = calc(r+1,n-1) % 3;
            set<int>st; st.insert(a); st.insert(b); st.insert(c);
            if(st.size() == 1 || st.size() == 3){
                cout<<l+1<<" "<<r+1<<ln;
                return;
            }
        }
    }
    cout<<"0 0"<<ln;
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