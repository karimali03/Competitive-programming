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
    int a,n; cin>>a>>n;
    int x,y; cin>>x>>y; if(x>y) swap(x,y);
    string X = to_string(a);
    int sz = X.size();
    int r1=y,r2=0;
    for(int i = 0;i < sz ; i++){
        r1 *=10; r1 += x;
    }
    for(int i=1;i<sz;i++){
        r2 *= 10; r2 += y;
    }
    cout<<r1<<" "<<r2<<ln;
    auto calc = [](int a,int b,int c) -> int{
        int ret = a;
        for(int i=0;i<c;i++){
            ret *= 10; ret += b;
        }
        return ret;
    };
    int r3 = 0,r4 = -1;
    for(int i = sz-1 ; i >= 0 ; i--){
        int d = X[i]-'0';
        r3 *= 10;
        if(d == x){
            r3 += x;
        }else if(d == y){
            r3 += y;
        }else if(d > max(x,y)){
            r3 += calc(max(x,x),x,i);
            break;
        }else if(d < min(x,y)){
            r3 += calc(max(x,y),min(x,y),i);
        }else{
            r4 = r3 + calc(y,x,i);
            r3 += calc(x,y,i);
        }
    }
    int ans = abs(r1-a);
    ans = min(ans , abs(a-r2));
    ans = min(ans , abs(a-r3));
    if(r4 != -1) ans = min(ans , abs(1-r4));
    cout<<ans<<ln;
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