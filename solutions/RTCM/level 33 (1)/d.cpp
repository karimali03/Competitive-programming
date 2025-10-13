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



string L,R;
ll dp[20][2][2][2][11][11];
// pos, tight left, tight right ,started, property
// 0 , 1 , 1 , 0 , ----
ll rec(int pos, bool tl,bool tr,bool st,int mn,int mx) {
 
    if (pos == (int)L.size()){
         //  cout<<pos<<" "<<mn<<" "<<mx<<" "<<st<<" "<<(st ? mx-mn : 20)<<ln;
        return (st ? mx-mn : 20);
    } 
    ll &ret = dp[pos][tl][tr][st][mn][mx];
    if (~ret) return ret;
    ret = 20;
    
    int l = (tl ? L[pos] - '0' : 0);
    int r = (tr ? R[pos] - '0' : 9);
    for (int d = l; d <= r; d++) {
        bool ns = st || (d != 0);
       //cout<<st<<" "<<d<<" "<<ns<<ln;
     //   cout<<pos<<" "<<d<<" "<<ns<<" "<< rec(pos + 1, tl && (d == l), ns , tr && (d == r) , (ns ? min(d,mn): mn) , (ns ? max(d,mx) : mx) ) <<ln;
        ret = min<ll>(ret , rec(pos + 1, tl && (d == l) , tr && (d == r) , ns , (ns ? min(d,mn): mn) , (ns ? max(d,mx) : mx) ) );
    }
    return ret;
}
string res;

void build(int pos, bool tl,bool tr,bool st,int mn,int mx){
    if (pos == (int)L.size()) return;
    int opt = rec(pos,tl,tr,st,mn,mx);
  
    int l = (tl ? L[pos] - '0' : 0);
    int r = (tr ? R[pos] - '0' : 9);
    for (int d = l; d <= r; d++) {
        bool ns = st || (d != 0);
        int ret = rec(pos + 1, tl && (d == l) , tr && (d == r) , ns , (ns ? min(d,mn): mn) , (ns ? max(d,mx) : mx) );
        if(ret == opt){
            res.push_back((char)d+'0');
            build(pos + 1, tl && (d == l) , tr && (d == r) , ns , (ns ? min(d,mn): mn) , (ns ? max(d,mx) : mx) );
            return;
        }
    }

}


int dp_digit(int l,int r){
    L = to_string(l);
    R = to_string(r);
    while (L.size() < R.size()) L = '0' + L;
    memset(dp,-1,sizeof(dp));
    res.clear();
    int ans = rec(0,1,1,0,10,0);
    build(0,1,1,0,10,0);
    reverse(all(res));
    while (res.back() == '0') res.pop_back();
    reverse(all(res));
    return ans;
}

void solve(int test_case) {
    int l,r; cin>>l>>r;
    dp_digit(l,r);
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