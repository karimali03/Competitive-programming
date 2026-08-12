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



// pi[i] = longest proper prefix of s that is also suffix of s[0..i]
// on mismatch: jump to next smaller border using pi[j-1]
vector<int> prefix_function(const string &s){
    int n = s.size();
    vector<int> pi(n);
    int j = 0;

    for(int i = 1; i < n; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }

    return pi;
}

void solve(int test_case) {
    string a,b; cin>>a>>b;
    string t1 = a + '#' + b;
    string t2 = b + '#' + b;
    auto p1 = prefix_function(t1);
    auto p2 = prefix_function(t2);
    int res = 0;
    int n = a.size();
    cout<<p1<<ln;
    cout<<p2<<ln;
    int j1 = p1.back();
    int j2 = p2.back();
    while(j1 > 0 && j2 > 0){
        cout<<j1<<" "<<j2<<endl;
        if(j1 > j2) j1 = p1[j1-1];
        else if(j2 > j1) j2 = p2[j2-1];
        if(j1 == j2){
            res++; 
            if(j1){
                j1 = p1[j1-1];
                j2 = p2[j2-1];
            }
        }
    }
    if(a[0] == b[n-1] && a[n-1] == b[0]) res++;
    cout<<res<<ln;
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