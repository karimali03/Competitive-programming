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

int zz(string &s){
    int cnt = 0;
    for(auto &it : s) if(it == '0') cnt++;
    return cnt;
}
pair<int,int> s1(int n,int x) {
    string s = to_string(n);
    int mn = zz(s);
    int val = 0;
    for(int i = 0; i < x ; i++){
        int cur = i + n;
        string a = to_string(cur);
        if(zz(a) < mn && stoll(a) <= x){
            mn = zz(a);
            val = i;
        }
    }
    return {mn,val};
}


void s2() {
    int n,x; cin>>n>>x;
    string s = to_string(n);
    int sz = s.size();
    string res = s;
    int cur = zz(s);
    for(int i = sz-1 ; i >= 0 ; i--){
        s[i] = '1';
        if(stoll(s) <= x && cur > zz(s)){
            res = s;
        } 
        cur = zz(s);
    }
    int ans = stoll(res) - n;
    cout<<ans<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin>>t;
    while(t--) s2();
    // for(int i = 1 ; i <= 100 ; i++){
    //     for(int j = i ; j <= 200 ; j++){
    //         auto c1 = s1(i,j);
    //         auto c2 = s2(i,j);
    //         if(c1.first != c2.first || c1.second != c2.second){
    //             cout<<i<<" "<<j<<" "<<c1.first<<" "<<c1.second<<" "<<c2.first<<" "<<c2.second<<ln; 
    //         }
    //     }
    // }

    return 0;
}