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

int clearMSBtoI(int num,int i){
    // 1234i5678
    // 000005678
    int mask = (1 << i) - 1;
    return num & mask;
}

int clearItoLSB(int num,int i){
    //  12345i678
   //   123450000
   int mask = -1 << ( i + 1 );
   return num & mask;
}

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    int x = 0; f(i,0,n) x|=v[i];
    vi ans(32);
    int cost = 0;
    for(int i = co(x)+1 ; i < 32 ; i++){
         int Or = 0;
        for(auto it : v) Or|=it; 
        int bit = 0;
        while((Or>>bit)&1) bit++; 
        while(true){
            Or = 0;
            for(auto it : v) Or|=it;
            if(co(Or) == i) break;
            while(bit >= 0 && (Or>>bit)&1) bit--;
            if(bit == -1) break;
            sort(all(v),[&](int x,int y){
                x = clearMSBtoI(x,bit);
                y = clearMSBtoI(y,bit);
                return x > y;
            });
            cost += (1ll<<bit) - clearMSBtoI(v[0],bit); 
            v[0] = (1ll<<bit) + clearItoLSB(v[0],bit);
        }
        ans[i] = cost;
    }
    while(q--){
        int x; cin>>x;
        auto it = upper_bound(all(ans) , x) - ans.begin() - 1;
        cout<<it<<ln;
    }
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