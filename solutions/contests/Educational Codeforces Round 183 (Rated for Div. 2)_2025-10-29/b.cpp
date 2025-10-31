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
    int n,k; cin>>n>>k;
    string s; cin>>s;
    if(n == k){
        string res(n,'-');
        cout<<res<<ln;
        return;
    }
    int l = 0 , r = n-1;
    string res(n,'+');
    pair<int,int>x = {-1,-1};
    for(int i = 0 ;i < k ; i++){
        if(s[i] == '1'){
            if(x.first != -1){
                res[x.second] = '-';
                x.second--;
                res[r] = '?'; r--;
            }
            else res[r] = '-',r--;
        }else if(s[i] == '0'){
            if(x.first != -1){
                res[x.first] = '-';
                x.first++; 
                res[l] = '?'; l++;
            }
            else res[l] = '-',l++;
        }else{
            if(x.first == -1) x = {l,r};
            res[l] = res[r] = '?'; l++,r--;
        }
    }
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