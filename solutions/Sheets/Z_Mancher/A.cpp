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
vector<int> z_function(const string& s) {
    int n = s.length();
    vector<int> z(n, 0);
    int l = 0, r = 0; // [l, r] make a window which matches with prefix of s
    
    for (int i = 1; i < n; i++) {
        // If i is within the rightmost matched window, use previously computed values
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        
        // Attempt to expand the match
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        
        // If the new match extends past the right bound, update the window
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    z[0] = n;
    return z;
}
void solve(int test_case) {
    string s; cin>>s;
    auto z = z_function(s);
  //  cout<<z<<ln;
    int n = s.size();
    vi frq(n+1);
    f(i,0,n) frq[z[i]]++;
    for(int i = n-1 ; i > 0 ; i--) frq[i] += frq[i+1];
    int c = 1;
    vii op;
    for(int i = n-1 ; i >= 0 ; i--){
        if(z[i] == c){
           op.push_back({c,frq[z[i]]});
        }
        c++;
    }
    cout<<op.size()<<ln;
    for(auto &it : op){
        cout<<it[0]<<" "<<it[1]<<ln;
    }
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