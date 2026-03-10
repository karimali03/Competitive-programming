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

const int N = 1005;
int res[N][N]{};
void chk(int n,int x,int y){
    if(x < y) swap(x,y);
    int a = y;
    x -= y;
    for(int i = y ;i < n ; i++){
        if(x) a++,x--;
        int rem = n - i - 1;
        if(x && y+rem < a) return;
    }
    res[x][y] = 1;
}
void solve() {
    int n,x,y; cin>>n>>x>>y;
    if(x < y) swap(x,y);
    if(x > n || y > n){
      //  return false;
        cout<<"Impossible\n";
        return;
    }
    if(x == y){
      //  return true;
        cout<<"Possible\n";
        return;
    }
    n-=y;
    x-=y; y = 0;
    int m = (n+1)/2;
    if(n%2==0) m++;
    if(x <= m){
       //  return true;
        cout<<"Possible\n";
        return;
    }
    cout<<"Impossible\n";
    // return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) solve();
    
  

    return 0;
}