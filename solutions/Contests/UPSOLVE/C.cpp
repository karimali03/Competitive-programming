#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld  double
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

const int N = 505;
const int M = 15;
int n,k,s,h;
array<ld,4> v[N];

ld P(int g,int d){
    // g+1 / (days + 2)
    return (ld)(g+1) / (ld)(d + 2);
}


ld cur[N][M][M]{};
ld nxt[N][M][M]{};
void solve(int test_case) {
    cin>>n>>k>>s>>h;
    for(int i = 0;i < n ; i++){
        for(int j = 0;j < 4 ; j++) cin>>v[i][j];
    }
    for(int g = 0; g <= n ; g++){
        for(int hr = 0; hr < h ; hr++){
            for(int bat = 0; bat <= k ; bat++){
                nxt[g][hr][bat] = 1.0;
            }
        }
    }
    
    for(int i = n-1 ; i >= 0 ; i--){
        memset(cur,0,sizeof(cur));
        for(int g = 0; g <= i ; g++){
            ld p = P(g,i);
            for(int hr = 0; hr < h ; hr++){
                for(int bat = 0 ; bat <= k ; bat++){
                    // hide
                    ld ch1 = (1 - p) * nxt[g][hr+1][bat] + p * nxt[g+1][hr+1][bat];
                    // battery
                    ld ch2 = (1 - p) * v[i][0] * (1 - v[i][3]) * nxt[g][hr+1][min(k,bat+1)];
                    ch2 += (1 - p) * (1 - v[i][0]) * (1 - v[i][3]) * nxt[g][hr+1][bat];
                    if(bat >= 2){
                        ch2 += (1-p) * v[i][0] * v[i][3] * nxt[g][hr+1][bat-1];
                        ch2 += (1-p) * (1-v[i][0]) * v[i][3] * nxt[g][hr+1][bat-2];
                    }
                    // food
                    ld ch3 = (1-p) * v[i][1] * (1-v[i][2]) * (1 - v[i][3]) * nxt[g][0][bat];
                    ch3 += (1-p) * (1-v[i][1]) * (1-v[i][3]) * nxt[g][hr+1][bat];
                    if(bat >= 2){
                        ch3 += (1-p) * v[i][1] * (1-v[i][2]) * v[i][3] * nxt[g][0][bat-2];
                        ch3 += (1-p) * (1-v[i][1]) * v[i][3] * nxt[g][hr+1][bat-2];
                    }
                    cur[g][hr][bat] = max<ld>({ch1,ch2,ch3});
                }
            }
        }
        swap(cur,nxt);
    }

    ld res = nxt[0][0][s];
    cout<<fixed<<setprecision(10)<<res<<ln;
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