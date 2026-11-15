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


const int N = 100005;
vector<pair<int,int>> g[N];
int sz[N];
bool del[N];
vector<pair<int,int>>path[N];
bool color[N]{};
multiset<int> st[N];
int get_size(int u,int p){
    sz[u]=  1;
    for(auto &[it,w] : g[u]) if(it != p && !del[it]){
        sz[u] += get_size(it,u);
    }
    return sz[u];
}
int get_centriod(int u,int p,int tot){
    for(auto &[it,w] : g[u]) if(it != p && !del[it]){
        if(sz[it] * 2 > tot) return get_centriod(it,u,tot);
    }
    return u;
}

void add(int x,int p,int cen,int d){
    path[x].push_back({cen,d});
    for(auto &[it,w] : g[x]) if(it != p && !del[it]){
        add(it,x,cen,d+w);
    }
}
void decompose(int x){
    int xsz = get_size(x,-1);
    int cent = get_centriod(x,-1,xsz);
    // calc answer for this centriod
    path[cent].push_back({cent,0});
    for(auto &[it,w] : g[cent]) if(!del[it]){
        add(it,cent,cent,w);
    }
    // clear ds for next centriod
    del[cent] = true;
    // decompse for next centriod
    for(auto &[it,w] : g[cent]) if(!del[it]){
        decompose(it);
    }
}

void solve(int test_case) {
    int n; cin>>n;
    for(int i=1;i<n;i++){
        int x,y,w; cin>>x>>y>>w; x--,y--;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }   
    decompose(0);
    int q; cin>>q;
    while(q--){
        int op; cin>>op;
        if(op == 1){
            int v,d,c; cin>>v>>d>>c; v--;
            for(auto &[a,b] : path[v]){
                if(b > d) continue;
                int rem = d-b;
                // A {TIME,REM,C}
            }
        }else{
            int v; cin>>v; v--;

        }
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