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

vi prefix_function(string &s,int st){
    int n = s.size();
    int sz = n - st;
    vi pi(sz);
    for(int i = 1 ; i < sz ; i++){
        int j = pi[i-1];
        while(j>0 && s[i+st] != s[j+st]) j = pi[j-1];
        if(s[i+st] == s[j+st]) j++;
        pi[i] = j;
    }
    return pi;
}


void solve(int test_case) {
    string s; cin>>s;
    int n = s.size();
    auto count = [](int num){
        int ret = 0;
        while(num){
            num/=10; ret++;
        }
        return ret;
    };
    vi dp(n+1,1e9);
    dp[n] = 0;
    for(int i = n-1 ; i >= 0 ; i--){
        auto pi = prefix_function(s,i);
        for(int x = i ; x < n ; x++){
            int sz = x-i+1;
            int cost = 1 + sz;
            int k = sz - pi[x-i];
            if(sz % k == 0) cost = count(sz/k) + k;
            dp[i] = min(dp[i] , cost + dp[x+1]);
        }
    }
    cout<<dp[0]<<ln;
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


// String Periodicity and Compression Notes

// ### Definition: String Periodicity
// A string 's' is said to have a period of 'k' if the character at any position 'i' is the same as the character at position 'i + k'.
// - s[0] = s[k] = s[2k] = ...
// - s[1] = s[k+1] = s[2k+1] = ...
// - ...and so on for all indices.

// ### Checking for Periodicity

// There are several ways to check if a string or substring is periodic with period 'k':

// 1.  **Substring Equality Check:**
//     A range [L, R] of a string is periodic with period 'k' if the substring from [L+k, R] is equal to the substring from [L, R-k].
//     - `IF s[L+k ... R] == s[L ... R-k] THEN the range [L, R] has a period of 'k'`

// 2.  **Prefix-Suffix Overlap Check (using KMP Prefix Function):**
//     This is a common method for checking the periodicity of the *entire* string of length 'n'.
//     - Let 'p' be the length of the longest proper prefix of 's' that is also a suffix of 's' (this is pi[n-1] in KMP).
//     - Let k = n - p.
//     - `IF the prefix of length (n-k) == the suffix of length (n-k)`
//     - `THEN the entire string 's' is periodic with a period of 'k'`
    
//     (Note: `p = n-k`, so a prefix of length `n-k` is the same as a prefix of length `p`. This check is equivalent to finding the last value of the KMP prefix function.)

// ### Application: String Compression
// Periodicity is the key to string compression.

// - If a string 's' of length 'n' has a period 'k' (as determined by the prefix-suffix check above), you must then check if 'k' divides 'n'.
// - `IF 'k' divides 'n' (i.e., n % k == 0)`
// - `THEN the string 's' can be compressed.` The shortest repeating block that forms 's' is the prefix of length 'k' (i.e., s[0 ... k-1]).
// - `ELSE (if 'k' does not divide 'n')`
// - `THEN no effective compression is possible,` and the shortest "compressed" string is 's' itself.