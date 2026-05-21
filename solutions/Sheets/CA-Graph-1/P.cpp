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

#define loop(u,e,v) for (int e = head[u], v; ~e && (v = to[e], 1); e = nxt[e])
const int N = 1005;
const int M = 200005;
int head[N],to[M],nxt[M],ne;
void init(int n){
    ne = 0;
    memset(head,-1,n*sizeof(head[0]));
}
void add(int u,int v,int w = 0){
    to[ne] = v;
    nxt[ne] = head[u];
    head[u] = ne++;
}

int dist(int x1,int y1,int x2,int y2){
    return  (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}
bool tangent(tuple<int,int,int> &a,tuple<int,int,int> &b){
    auto [x1,y1,r1] = a;
    auto [x2,y2,r2] = b;
    return dist(x1,y1,x2,y2) == (r1+r2)*(r1+r2);
}


int vis[N]{};
int l,r;
bool vld;

void bipartie(int x,int color){
        vis[x] = color;
        int tag = color^3;
        if(color == 1) l++;
        else r++;
        loop(x,e,v){
            if(!vis[v])  bipartie(v,tag);
            else if(vis[v] != tag) vld = false;
        }
}
void solve(int test_case) {
    int n; cin>>n;
    init(n);
    vector<tuple<int,int,int>>cor(n);
    f(i,0,n){
        int x,y,r; cin>>x>>y>>r;
        cor[i] = {x,y,r};
    }
    for(int i = 0;i < n ; i++){
        for(int j = i+1 ; j < n ; j++){
            if(tangent(cor[i],cor[j])){
                add(i,j); add(j,i);
            }
        }
    }
    l = r = 0;
    vld = true;
    f(i,0,n) if(!vis[i]){
        bipartie(i,1);
        if(vld && l != r){
            YES; return;
        }
        l = r = 0;
        vld = true;
    }
    NO;
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