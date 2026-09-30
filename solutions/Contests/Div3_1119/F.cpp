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
    int n; cin>>n;
    vi v(n); cin>>v;
    string s; cin>>s;
    vi c(2);
    int inv = 0;
    for(int i = 0;i < n ; i++){
        if(v[i] == 0) inv += c[1];
        c[v[i]]++;
    }   
    vi cur;
    for(int i = 0;i < n ; ){
        while(i < n && v[i] == 0) i++;
        if(i < n){
            int c = 0; i++;
            while(i < n && v[i] == 0) c++,i++;
            cur.push_back(c);
        }
    }
    int sz = cur.size();
    int l = 0,r = sz-1;
    int sum = 0;
    for(auto &it : cur) sum += it;
  //  cout<<sum<<ln;
  //  cout<<cur<<ln;
    cout<<inv<<" ";
    for(int i = 0;i < n ; i++){
        while(r >= l && cur[r] == 0) r--;
        if(l > r){
            cout<<inv<<" "; continue;
        }
        if(s[i] == '1'){
            inv -= sum;
            sum -= cur[l++];
        }else{
            inv -= (r-l+1);
            sum--;
            cur[r]--;
        }
        cout<<inv<<" ";
    }
    cout<<ln;
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