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


// Extended Euclidean Algorithm
long long egcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Combine two congruences: x ≡ a1 (mod m1), x ≡ a2 (mod m2)
// Returns {solution, new_modulus}, or {-1,-1} if no solution
pair<long long,long long> crt_pair(long long a1, long long m1, long long a2, long long m2) {
    long long x, y;
    long long g = egcd(m1, m2, x, y);
    if ((a2 - a1) % g != 0) return {-1, -1}; // no solution

    long long lcm = m1 / g * m2;
    long long res = (a1 + (a2 - a1) / g * x % (m2/g) * m1) % lcm;
    if (res < 0) res += lcm;
    return {res, lcm};
}

// General CRT for multiple congruences
// Input: vector of (remainder, modulus)
// Output: {solution, lcm}, or {-1,-1} if inconsistent
pair<long long,long long> crt(const vector<pair<long long,long long>> &congruences) {
    long long a = congruences[0].first;
    long long m = congruences[0].second;

    for (int i = 1; i < (int)congruences.size(); i++) {
        auto [a2, m2] = congruences[i];
        auto res = crt_pair(a, m, a2, m2);
        if (res.first == -1) return {-1, -1}; // no solution
        a = res.first;
        m = res.second;
        if(a > 1e9) return {1e9+1,-1};
    }
    return {a, m};
}

void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n),p(n); cin>>a>>b>>p;
    f(i,0,n) a[i]--,b[i]--,p[i]--;
    vi vis(n);
    vector<pair<int,int>>ret;
    // for(int i = 0 ;i  < n;  i++){
    //     if(!vis[p[i]]){
    //         vi cycle;
    //         int cur = p[i];
    //         while (!vis[cur]){
    //             cycle.push_back(cur);
    //             vis[cur] = 1;
    //             cur = p[cur]; 
    //         }
      
    //         int l = 0,r = 0;
    //         int cnt = 0;
    //         int sz = cycle.size();
    //         while(cnt < sz && a[cycle[l]] != b[cycle[r]])  r++,cnt++;
    //         r%=sz;
    //         for(int j = 0 ; j < sz ; j++){
    //             if(a[cycle[l]] != b[cycle[r]]){
    //                  cout<<"IMPOSSIVEL\n"; return;
    //             }
    //             l = (l+1)%sz; r = (r+1)%sz;
    //         }
    //         ret.push_back({cnt,cycle.size()});
    //     }
    // }
    ret.push_back({1,3}); ret.push_back({0,2});
    for (int i = 0; i < t; i++) {
        ret[i].first = normalize(ret[i].first, ret[i].second);
    }

    auto ans = crt(ret);
    if(ans.first == -1) cout<<"IMPOSSIVEL\n"<<ln;
    else if(ans.first == 1e9+1) cout<<"DEMAIS"<<ln;
    else cout<<ans.first<<ln;
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