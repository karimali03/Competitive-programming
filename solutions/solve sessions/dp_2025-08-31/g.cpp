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

const int N = 205;
const int MOD = 1e9+7;

// dp[i][prv][cnt][ch][n][k] would be too big, so we just cache per (n,k) with a versioning trick
int dp[N][N][N][2];
int sdp[N][N][N][2];
int vis[N][N][N][2];   // store k of last computation
int vis2[N][N][N][2];  // store k of last computation for sdp
int current_n, current_k, current_ver = 1;

// recursive dp
function<int(int,int,int,int)> prefix;
function<int(int,int,int,int)> rec;

int solve_nk(int n,int k){
    current_n = n;
    current_k = k;
    current_ver++; // new version for this (n,k)

    rec = [&](int i,int prv,int cnt,int ch)->int{
        if(i==n) return (ch==1);
        int &ret = dp[i][prv][cnt][ch];
        if(vis[i][prv][cnt][ch] == current_ver) return ret;
        vis[i][prv][cnt][ch] = current_ver;

        ret = 0;
        // <
        if(cnt != k){
            int nc = (cnt==k-1 ? 1 : ch);
            ret = (prefix(i+1,i+1,cnt+1,nc) - prefix(i+1,prv,cnt+1,nc) + MOD)%MOD;
        }
        // >
        (ret += prefix(i+1,prv,1,ch))%=MOD;
        return ret;
    };

    prefix = [&](int i,int prv,int cnt,int ch)->int{
        if(prv==0) return 0;
        int &ret = sdp[i][prv][cnt][ch];
        if(vis2[i][prv][cnt][ch] == current_ver) return ret;
        vis2[i][prv][cnt][ch] = current_ver;

        return ret = (rec(i,prv,cnt,ch)%MOD + prefix(i,prv-1,cnt,ch)%MOD)%MOD;
    };

    return rec(1,1,1,(k==1?1:0));
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
  
   // freopen("permutations.in","r",stdin);

    int T; cin>>T;
    while(T--){
        int n,k; cin>>n>>k;
        cout << solve_nk(n,k) << "\n";
    }
    return 0;
}