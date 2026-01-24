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


vector<int> prefix_function(vector<int> &s){
    int n = s.size();
    vector<int>pi(n);
    int j = 0;
    for(int i = 1;i < n ; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j-1]; 
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
// count each occurence of s as substr in t
vector<int> find_substr(vi &s,vi &t){
    vi cur;
    for(auto &it : s) cur.push_back(it);
    cur.push_back(270);
    for(auto &it : t) cur.push_back(it);
    int n = s.size();
    int sz = cur.size();
    auto pi = prefix_function(cur);
    vi ret(n+1);
    for(int i = n+1 ; i < sz ; i++){
        ret[pi[i]]++;  
    }
    for(int i = n-1 ; i >= 0 ; i--) ret[i] += ret[i+1];
    return ret;
}

void solve(int test_case) {
    string a,b; 
    getline(cin,a); 
    getline(cin,b);
    vi aa,bb;
    for(unsigned char it : a) aa.push_back((int)it);
    for(unsigned char it : b) bb.push_back((int)it);
    int cnt; cin>>cnt;
    auto ret = find_substr(bb,aa);
    int res = 0;
    int n = b.size();
    for(int i = 0; i <= n ; i++){
        if(ret[i] >= cnt) res = i;
    }
    if(res == 0) cout<<"IMPOSSIBLE";
    else cout<<b.substr(0,res)<<ln;
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