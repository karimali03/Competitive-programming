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

int n,m;
const int N = 100005;
const int B = 450;
vector<int> g[N];
vector<int> hg[N];
bool hv[N];
int vr[N];
int frq[B+20][N]{};
int id[N];
void solve(int test_case) {
    cin>>n>>m;
    int res = 0;
    for(int i = 0;i < n ; i++) cin>>vr[i];
    for(int i = 0;i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
        if(vr[x] != vr[y]) res++;
    }    
    for(int i = 0 ; i < n ; i++){
        if(g[i].size() > B) hv[i] = true;
    }
    int c = 0;
    for(int i = 0;i < n ; i++){
        if(hv[i]) id[i] = c++;
        for(auto &it : g[i]){
            if(hv[i]) frq[id[i]][vr[it]]++;
            if(hv[it]) hg[i].push_back(it);
        } 
    }

    int q; cin>>q;
    while(q--){
        int x,y; cin>>x>>y; x--;
        if(hv[x]){
            res += frq[id[x]][vr[x]];
            res -= frq[id[x]][y];
            for(auto &it : hg[x]){
                frq[id[it]][vr[x]]--;
                frq[id[it]][y]++;
            }
        }else{
            for(auto it : g[x]){
                if(vr[it] == vr[x]) res++;
                if(vr[it] == y) res--;
                if(hv[it]){
                    frq[id[it]][vr[x]]--;
                    frq[id[it]][y]++;
                }
            }
        }
        vr[x] = y;
        cout<<res<<ln;
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