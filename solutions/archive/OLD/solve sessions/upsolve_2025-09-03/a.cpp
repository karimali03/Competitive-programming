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

const int OO = 1e9;
struct node {
    int x, y, d;
    node(int x=0,int y=0,int d=0):x(x),y(y),d(d){}
    bool operator<(const node &rhs) const {
        return d > rhs.d;
    }
};

void solve(int test) {
    int n,m; cin>>n>>m;
    vii v(n, vi(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char ch; cin>>ch; 
            v[i][j] = ch-'0';
        }
    }

    int sx,sy,tx,ty; cin>>sx>>sy>>tx>>ty;
    int k; cin>>k;
    vector<string> s(k);
    for(int i=0;i<k;i++) cin>>s[i];

    vii dist(n, vi(m, OO));
    priority_queue<node> q;
    q.push({sx,sy,0});

    while(!q.empty()){
        auto cur = q.top(); q.pop();
        if(dist[cur.x][cur.y] != OO) continue;
        dist[cur.x][cur.y] = cur.d;
        if(cur.x == tx && cur.y == ty){
            cout<<cur.d<<ln;
            return;
        }
        for(auto &str : s){
            int cnt=0, i=cur.x, j=cur.y;
            for(char ch: str){
                if(ch=='D' && i+1<n && !v[i+1][j]) i++,cnt++;
                else if(ch=='U' && i>0 && !v[i-1][j]) i--,cnt++;
                else if(ch=='L' && j>0 && !v[i][j-1]) j--,cnt++;
                else if(ch=='R' && j+1<m && !v[i][j+1]) j++,cnt++;
            }
            if(dist[i][j] == OO) 
                q.push({i,j,cur.d+cnt});
        }
    }

    
    NA;
    
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