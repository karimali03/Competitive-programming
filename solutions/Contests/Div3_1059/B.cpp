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


bool pln(string &s,int sz){
    for(int i =0;i < sz/2 ; i++){
        if(s[i] != s[sz-i-1]) return false;
    }
    return true;
}

bool chk(string &s,int sz){
    for(int i = 1 ; i < sz ; i++){
        if(s[i] < s[i-1]) return false;
    }
    return true;
}
void solve(int test_case) {
    int n; cin>>n;
    string s; cin>>s;
    string a = s , b = s;
    for(int m = 0; m < (1<<n) ; m++){
        bool vld = true;
        int c1 = 0 , c2 = 0;
        for(int i = 0; i < n ; i++){
            if((m>>i)&1){
                a[c1++] = s[i];
            }else{
                b[c2++] = s[i];
            }
        }
        if(pln(b,c2) && chk(a,c1)){
            cout<<c1<<ln;
            for(int i =0;i < n ; i++){
                if((m>>i)&1) cout<<i+1<<" ";
            }
            cout<<ln;
            return;
        }
    }
    NA;
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