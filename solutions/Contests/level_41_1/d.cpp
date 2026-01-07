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
    if(i < 0) return num;
    //  12345i678
   //   123450000
   int mask = -1ll << ( i + 1ll );
   return num & mask;
}

// get the most significant bit
int MSB(int x){
    ll msb = 0;
    while (x){
        x >>= 1ll;
        msb++;
    }
    return msb - 1;
}

void solve(int test_case) {
   int n,m; cin>>n>>m;
   
   if(co(n) == 1){
        NA;
        return;
   }
  // cout<<bitset<64>(n).to_string()<<"\n"<<bitset<64>(m).to_string()<<ln; 

   int a = MSB(n);
   int b = MSB(m);
   vi opt;
   for(int i = 63 ; i >= 0 ; i--){
        if((n>>i)&1ll) opt.push_back(i);
        if(opt.size() == 2) break;
   }
   if(a == b || ((n>>b)&1ll) ){
       cout<<"1\n"<<n<<" "<<m<<ln;
   }else if(b < opt[1]){
        cout<<"2\n";
        cout<<n<<" ";
        n = clearItoLSB(n^(1ll<<a),opt[1]-1);
        n |= m;
        cout<<n<<" ";
        cout<<m<<ln;
   }else NA;

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