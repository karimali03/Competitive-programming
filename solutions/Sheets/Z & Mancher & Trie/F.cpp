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


/*

d1[i] -> odd center i
range = [i-d1[i]+1, i+d1[i]-1]

d2[i] -> even center between i-1,i
range = [i-d2[i], i+d2[i]-1]

odd length  = 2*d1[i]-1
even length = 2*d2[i]

sum(d1)+sum(d2) = # palindromic substrings

*/

const int N = 10005;
int d1[N]{},d2[N]{};
int manacher(string &s){
    int n = s.size();
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r ? 1 : min(d1[l+r-i], r-i+1));
    
        while (i-k >= 0 && i+k < n && s[i-k] == s[i+k])
            k++;
    
        d1[i] = k--;
    
        if (i+k > r) {
            l = i-k;
            r = i+k;
        }
    }
    
    // even: [i-d2[i] ... i+d2[i]-1]
    int res = 0;
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r ? 0 : min(d2[l+r-i+1], r-i+1));
    
        while (i-k-1 >= 0 && i+k < n && s[i-k-1] == s[i+k])
            k++;
    
        d2[i] = k--;
    
        if (i+k > r) {
            l = i-k-1;
            r = i+k;
        }
        res += d1[i] + d2[i];
    }
    return res;
}

void solve(int test_case) {
    int n; cin>>n;
    string s;
    while(n--){
        char c; cin>>c;
        if(c == '-') s.pop_back();
        else s += c;
        cout<<manacher(s)<<" ";
    }
    cout<<ln;
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