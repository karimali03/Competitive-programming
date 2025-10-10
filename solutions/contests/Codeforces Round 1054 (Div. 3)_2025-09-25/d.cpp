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
    int n,k,l,r; cin>>n>>k>>l>>r;
    vi v(n); cin>>v;
    map<int,int>mp;
    set<int>st;
    int sr = 0;
    int cnt = 0;
    v.push_back(1e9+1);
    for(int i = 0 ;i  <= n ;i++){
        int sz = st.size();
        st.insert(v[i]); mp[v[i]]++;
        int nsz = st.size();
        while(i-sr+1 > r || st.size() > k){
            mp[v[sr]]--;
            if(mp[v[sr]] == 0) st.erase(v[sr]);  sr++;   
            if(sz == k && i-sr >= l && i-sr <= r && st.size() == nsz) cnt++;
        }
        if( i != n && (int)st.size() == k && (i-sr+1) >= l && (i-sr+1) <= r) cnt++;
         cout<<st.size()<<" "<<sr<<" "<<i<<" "<<(i-sr+1)<<" "<<cnt<<ln;
    }

    cout<<cnt<<ln;
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