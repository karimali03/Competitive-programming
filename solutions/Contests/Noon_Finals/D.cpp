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


const int mod = 998244353;

int add(int a, int b) {
    return ((a % mod) + (b % mod)) % mod;
}

int mul(int a, int b) {
    return ((a % mod) * (b % mod)) % mod;
}

int fp(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = a * res % mod;
        a = a * a % mod;
        b>>=1;
    }

    return res;
}


int pw[25];
void solve(int test_case) {
    int n; cin>>n;
    for(int i = 0;i < 25 ; i++) pw[i] = fp(fp(2,i),mod-2);
    vector<int>v(1<<n);
    int idx = 0;
    vi c1(1<<n),c2(1<<n);
    for(int i = 0;i < (1<<n) ; i++){
        char x; cin>>x;
        if(x == '1')  v[i]  = 1,c1[i]++;
        else if(x == '?') v[i] = pw[1],c2[i]++;
        else if(x == '0') v[i] = 0;
        else v[i] = 1,idx=i;
    }
    f(i,1,(1<<n)) c1[i] += c1[i-1] , c2[i] += c2[i-1];
   
    int l,r;
    if(idx&1) l = idx-1 , r = idx;
    else l = idx , r = idx+1;
    int res = 0;
    (res += v[l] * v[r])%=mod;
    map<pair<int,int>,pair<int,int>>pr;
    function<void(int,int)> tr = [&](int x,int y){
        if(x == l && y == r) return;
        if(l > (x+y)/2){
            pr[{(x+y)/2+1,y}] = {x,y};
            tr((x+y)/2 + 1 , y);
        }else{
            pr[{x,(x+y)/2}] = {x,y};
            tr(x,(x+y)/2);
        }
    };
  /// cout<<"...."<<endl;
    tr(0,(1<<n)-1);
    pr[{0,(1<<n)-1}] = {-1,-1};
    int lvl = 1;
    while(true){
        auto cur = pr[{l,r}];
        if(cur.first == -1) break;
       // cout<<cur.first<<" "<<cur.second<<endl;
        int cc1 = c1[cur.second] - (cur.first == 0 ? 0 : c1[cur.first-1]);
        int cc2 = c2[cur.second] - (cur.first == 0 ? 0 : c2[cur.first-1]);
        cc1 -= c1[r] - (l ==0 ? 0 : c1[l-1]);
        cc2 -= c2[r] - (l == 0 ? 0 : c2[l-1]);
       // cout<<cc1<<" "<<cc2<<ln;
        (res += ((cc1 * pw[lvl])%mod * pw[lvl])%mod)%=mod;
        (res += ((cc2 * pw[lvl+1])%mod * pw[lvl])%mod)%=mod;
        lvl++;
        l = cur.first , r = cur.second;
        
    }
    cout<<res<<ln;
    // function<pair<int,int>(int,int)> calc = [&](int l,int r) -> pair<int,int> {
    //     if(r == l+1){
    //         pair<int,int> ret;
    //         ret.second = 0;
    //         ret.first = ((v[l]*p2)%mod + (v[r]*p2)%mod)%mod;
    //         if(idx == l || idx == r){
    //             (res += v[l]*v[r])%=mod;
    //             ret.first = p2;
    //             ret.second = 1;
    //         }
    //         // cout<<l<<" "<<r<<" "<<ret.first<<" "<<v[l]<<" "<<v[r]<<ln;
    //         // cout<<res<<ln;
    //         return ret;
    //     }
    //     auto a = calc(0,(l+r)/2);
    //     auto b = calc((l+r)/2+1,r);
    //   //  cout<<a.first<<" "<<a.second<<" "<<b.first<<" "<<b.second<<ln;
    //     if(a.second == 1){
    //         (res += a.first*b.first)%=mod;
    //         pair<int,int> ret;
    //         ret.second = 1;
    //         ret.first = (a.first*p2)%mod;
    //         return ret;
    //     }else if(b.second == 1){
    //        // cout<<res<<ln;
    //         // cout<<(a.first*b.first)%mod<<" "<<(fp(2,mod-2)*fp(2,mod-2))%mod<<ln;
    //         (res += a.first*b.first)%=mod;
    //        // cout<<res<<ln;
    //         pair<int,int> ret;
    //         ret.second = 1;
    //         ret.first = (p2*b.first)%mod;
    //         return ret;
    //     }else{
    //         pair<int,int> ret;
    //         ret.second = 0;
    //         ret.first = (( p2 * a.first)%mod + (p2 * b.first)%mod)%mod;
    //         return ret;
    //     }
    // };
    // calc(0,(1<<n)-1);
    // cout<<res<<ln;
  
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