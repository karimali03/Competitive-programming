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
const int N = 1e7 + 5;
// spf ( smallest prime factor )
int spf[N];
void SPF(){   //  O(n*log(log(n)))
  // 1. Standard Sieve to find the Smallest Prime Factor (spf)
      for (int i = 2; i < N; i++) spf[i] = i;
      for (int i = 2; i * i < N; i++) {
          if (spf[i] == i) {
              for (int j = i * i; j < N; j += i) {
                  if (spf[j] == j) spf[j] = i;
              }
          }
      }
}


int calc(int n,int x,vi &v){
    int cnt =0;
    for(int i = 0;i < n ; i++){
        if(x >= v[i]){
            cnt++;
            if(x < 4);
            else{
                int mx = 0;
                for(int m = x/2 ; m > 1 ; m--){
                    mx = max(mx , v[i] % m);
                }
                x += mx;
            }
        }else{
            if(x < 4) x -= v[i];
            else{
                int mn = 1e9;
                for(int m = x/2 ; m > 1 ; m--){
                    mn = min(mn , v[i] % m);
                }
                x -= mn;
            }   
        }

    }
    return cnt;
}
void solve(int test_case) {
    int n,x; cin>>n>>x;
    vi v(n); cin>>v;
    int cnt = 0;
  //  int c = calc(n,x,v);
    for(int i = 0;i < n ; i++){
        if(x >= v[i]){
            cnt++;
            if(x < 4);
            else if(v[i] < x/2) x += v[i];
            else{
                int m = x/2;
                int y = v[i];
                int cur = (m - y%m + (y/m)) / (1 + (y/m)) - 1;
                int nm = m - cur;
                x += y % nm;
            }
        }else{
            if(x < 4) x -= v[i];
            else if(spf[v[i]] > x/2) x--;    
            }
        }
      //  assert(c == cnt);
        cout<<cnt<<ln;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    SPF();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}