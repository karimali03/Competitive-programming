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


vector<pair<int,int>> fact(int n) {  // O(sqrt(n))
    map<int, int> res;
    for (int p = 2; p * p <= n; p++) {
        while (n % p == 0) {
            res[p]++;
            n /= p;
        }
    }
    if (n > 1) res[n]++; 
    vector<pair<int,int>> ret;
    for(auto [a,b] : res) ret.push_back({a,b});
    return ret;
}

void solve(int test_case) {
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    if(k == 1){
        cout<<n*(n+1)/2<<ln;
        return;
    }
    auto x = fact(k);
    bool vld = false;
    vi frq(x.size());
    auto add = [&](int a){
        bool valid = true;
        for(int i = 0 ; i < (int)x.size() ; i++){
            int c = 0;
            while(a%x[i].first == 0) a /= x[i].first,c++;
            frq[i] += c;
            valid &= (frq[i] >= x[i].second);
        }
        vld = valid;
    };
    
    auto rm = [&](int a){
        bool valid = true;
        for(int i = 0 ; i < (int)x.size() ; i++){
            int c = 0;
            while(a%x[i].first == 0) a /= x[i].first,c++;
            frq[i] -= c;
            valid &= (frq[i] >= x[i].second);
        }
        vld = valid;
    };
    
    int l = 0;
    int res = 0;
    for(int r = 0; r < n ; r++){
        add(v[r]);
        while(vld){
            res += (n - r);
            rm(v[l++]);
        }
    }
    cout<<res<<ln;
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