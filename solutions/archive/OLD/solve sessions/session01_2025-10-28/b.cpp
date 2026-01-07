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


const int LOG = 20;
const int MX = (1<<LOG);
int dp1[MX]{};
int dp2[MX]{};

void SOS1(){ // sum over subsets
    for(int bit=0;bit<LOG;bit++){
        for(int i=0;i<MX;i++) if((i>>bit)&1){
            dp1[i] += dp1[i^(1<<bit)];
        }
    }
}

void REV1(){
    for(int bit=0;bit<LOG;bit++){
        for(int i=MX-1;i>=0;i--) if((i>>bit)&1){
            dp1[i] -= dp1[i^(1<<bit)];
        }
    }
}

void SOS2(){ // sum over supersets
    for(int bit=0;bit<LOG;bit++){
        for(int i=MX-1;i>=0;i--) if((i>>bit)&1){
            dp2[i^(1<<bit)] += dp2[i];
        }
    }
}

void REV2(){
    for(int bit=0;bit<LOG;bit++){
        for(int i=0;i<MX;i++) if((i>>bit)&1){
            dp2[i^(1<<bit)] -= dp2[i];
        }
    }
}




void solve(int test_case) {
    int n; cin>>n;
    vi v(n); 
    for(int i = 0;i < n ; i++){
        cin>>v[i];
        dp1[v[i]]++; dp2[v[i]]++;
    }
    SOS1(); SOS2();
    for(int i = 0; i < n; i++){
        cout<<dp1[v[i]]<<" "<<dp2[v[i]]<<" ";
        int res3 = n - dp1[(MX-1)^v[i]];
        cout<<res3<<ln;
    }
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