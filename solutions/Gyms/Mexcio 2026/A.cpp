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

ld calc(ld r,ld angle){
    ld ret = r * r * PI  * (angle / 360.0);
    return ret;
}
void solve(int test_case) {
    int R,a,s; cin>>R>>a>>s;
    if(a == 360){
        cout<<fixed<<setprecision(7)<<calc((ld)R,180.0)<<" "<<calc((ld)R,90.0)<<ln;
        return;
    }
    ld l = (ld)s - (ld)(a / 2.0);
    ld r = (ld)s + (ld)(a / 2.0);
    ld sea = 0.0;
    ld nile = 0.0;
    // 0 180 
    if(l >= 0.0 && r <= 180.0){
        sea = calc((ld)R,(ld)a);
    }
    // 270 0
    else if(l >= 270.0 && r <= 360.0){
        nile = calc((ld)R,(ld)a);
    }
    else if(l >= 180.0 && r <= 270.0);
    else{
        if(r > 360.0){
            ld angSea = min<ld>(180.0 , r - 360.0);
            ld angNile = min<ld>(90.0 , 360.0 - l);
            sea += calc(R,angSea);
            nile += calc(R,angNile);
        }else if( l <= 0.0){
            ld angNile = min<ld>(90.0 , -l );
            ld angSea = min<ld>(180.0 , r );
            sea += calc(R,angSea);
            nile += calc(R,angNile);
        }
        if(l <= 180.0 && r >= 180.0){
            ld angSea = min<ld>(180.0 , 180.0 - l);
            sea += calc(R,angSea);
        }
        if(l <= 270.0 && r >= 270.0){
            ld angNile = min<ld>(90.0 , r - 270.0 );
            nile += calc(R,angNile);
        }
        if( l < -90.0){
            nile += calc(R,90.0);
        }
    }

    nile = min<ld>(nile,calc(R,90.0));
    sea = min<ld>(sea , calc(R,180.0));
    cout<<fixed<<setprecision(7)<<sea<<" "<<nile<<ln;

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