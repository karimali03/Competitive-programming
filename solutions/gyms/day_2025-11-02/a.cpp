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

const int N = 21;
const int MX = (1<<N);
int dp[MX]{};
int idx[6][6];
vector<pair<int,int>>dominoes;
void solve(int test_case) {
    int n; cin>>n;
    int mask = 0;
    for(int i = 0;i  < n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        pair<int,int> cur = minmax(x,y);
        auto it = idx[cur.first][cur.second];
        mask |= (1<<it);
    }
    cout<<dp[mask]<<ln;
}


bool cc(vector<int> g[],int st,int mask){
    queue<int>q; q.push(st);
    int vis = (1<<st);
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(auto it : g[cur]) if(!((vis>>it)&1)){
            vis |= (1<<it);
            q.push(it);
        }
    }
    return vis == mask;    
}

void SOS1(){
    for(int bit = 0; bit < N ; bit++){
        for(int i = 0;i < MX ; i++) if((i>>bit)&1){
            dp[i] += dp[i^(1<<bit)];
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i = 0 ;  i <= 6 ; i++){
        for(int j = i ; j <= 6 ; j++){
            idx[i][j] = dominoes.size();
            dominoes.push_back({i,j});
        }
    }
    for(int mask = 1; mask < MX ; mask++){
        vector<int> g[6];
        int deg[6]{};
        int x = 0 , st = -1;
        for(int i = 0; i < 21 ; i++) if((mask>>i)&1){
            int a = dominoes[i].first;
            int b = dominoes[i].second;

            if(st == -1) st = a;
            x = x | (1<<a) | (1<<b);
            deg[a]++,deg[b]++;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        bool vld = cc(g,st,x);
        int od = 0;
        for(int i = 0; i < 6 ; i++) if(deg[i]&1) od++;
        if(od > 2) vld = false;
        dp[mask] = vld;
    }
    SOS1();

    int t = 1;
    cin >> t; 
    for (int i = 1; i <= t; i++) {
       solve(i); 
    }

    return 0;
}