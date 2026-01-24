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
int clearItoLSB(int num,int i){
    //  12345i678
   //   123450000
   if(i < 0) return num;
   int mask = -1ll << ( i + 1ll );
   return num & mask;
}

bool isSubset(int sub, int super) {
    return (sub & super) == sub;
}

void solve(int test_case) {
    int n,x; cin>>n>>x;
    vi v(n);
    int xr = 0;
    f(i,0,n){
        cin>>v[i];
        xr ^= v[i];
    }
    if(xr > x){
        NA; return;
    }
    
    int mx = -1;
    {
        int cnt = 0;
        int cur = 0;
        int tot = 0;
        for(int j = 0; j < n ; j++){
            cur ^= v[j];
            if(isSubset(cur,x)){
                tot |= cur;
                cnt++ , cur = 0;
            }
        }
        if(isSubset(cur,x)){
            tot |= cur;
            if(tot <= x) mx = max(mx , cnt);
        }
    }

    for(int i = 0; i < 30 ; i++){
        if((x>>i)&1){
            int cnt = 0;
            int cur = 0;
            int tot = 0;
            for(int j = 0; j < n ; j++){
                cur ^= v[j];
                int a = clearItoLSB(x,i);
                int b = clearItoLSB(cur,i);
              //  cout<<j<<" "<<cur<<" "<<a<<" "<<b<<ln;
                if(isSubset(b,a) && !((cur>>i)&1) ){
              //      cout<<"---\n";
                    tot |= cur;
                    cnt++ , cur = 0;
                }
            }
            int a = clearItoLSB(x,i);
            int b = clearItoLSB(cur,i);
            if(isSubset(b,a) && !((cur>>i)&1)){
                tot |= cur;
                if(tot <= x) mx = max(mx , cnt);
            }
        }
    }

    
    cout<<mx<<ln;
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