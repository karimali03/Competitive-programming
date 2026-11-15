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
#define int ll
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


const int N = 200005;
vi g[N];
int sz[N];
bool del[N];
string s;
int cnt[1<<20]{};
int res[N]{};
int ans[N]{};
int get_size(int u,int p){
    sz[u]=  1;
    for(auto &it : g[u]) if(it != p && !del[it]){
        sz[u] += get_size(it,u);
    }
    return sz[u];
}
int get_centriod(int u,int p,int tot){
    for(auto &it : g[u]) if(it != p && !del[it]){
        if(sz[it] * 2 > tot) return get_centriod(it,u,tot);
    }
    return u;
}

void add(int x,int p,int msk,int delta){
    msk = msk ^ (1 << (s[x]-'a'));
    cnt[msk] += delta;
    for(auto &it : g[x]) if(it != p && !del[it]){
        add(it,x,msk,delta);
    }

}

void calc(int x,int p,int cent,int msk,int &c){
    msk = msk ^ (1 << (s[x]-'a'));
    int tag = msk ^ cent;
    res[x] = cnt[tag];
    if(co(tag) <= 1) c++;
    for(int i=0;i < 20 ; i++) res[x] += cnt[tag ^ (1 << i)];
    for(auto &it : g[x]) if(it != p && !del[it]){
        calc(it,x,cent,msk,c);
    }
}

int prop(int u,int p){
    for(auto &it : g[u]) if(it != p && !del[it]){
        res[u] += prop(it,u);
    }
    ans[u] += res[u];
    return res[u];
}
void decompose(int x){
    int xsz = get_size(x,-1);
    int cent = get_centriod(x,-1,xsz);
    // calc answer for this centriod
    cnt[0] = 1;
    int msk = (1 << (s[cent]-'a'));
    for(auto &it : g[cent]) if(!del[it]){
        add(it,cent,0,1);
    }
    int tot = 0;
    int c = 0;
    for(auto &it : g[cent]) if(!del[it]){
        add(it,cent,0,-1);
        calc(it,cent,msk,0,c);
        tot += prop(it,cent);
        add(it,cent,0,1);
    }
    ans[cent] += (tot + c) / 2  + 1;
    // clear ds for next centriod
    del[cent] = true;
    for(auto &it:  g[cent]) if(!del[it]){
        add(it,cent,0,-1);
    }
    // decompse for next centriod
    for(auto &it : g[cent]) if(!del[it]){
        decompose(it);
    }
}

void solve(int test_case) {
    int n; cin>>n;
    for(int i=1;i<n;i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    cin>>s;
    decompose(0);
    for(int i= 0;i<n;i++) cout<<ans[i]<<" ";
    cout<<ln;
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