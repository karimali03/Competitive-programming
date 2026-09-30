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

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vector<pair<int,int>>frq;
    vi cnt(101);
    for(int i=0;i<n;i++) cnt[v[i]]++;
    set<int>st;
    for(int i=0;i<n;i++) st.insert(v[i]);
    for(int i=100;i>=1;i--){
        if(!st.count(i)){
            continue;   
        }
        int c = cnt[i];
        for(int x=0;x<c;x++) cout<<i<<" ";
        st.erase(i);
        for(auto it = st.begin() ; it != st.end() ; ){
            c = min(cnt[*it] , cnt[i]);
            for(int x=0;x<c;x++) cout<<*it<<" ";
            cnt[*it] -= c;
            if(!cnt[*it]) it = st.erase(it);
            else ++it;
        }
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