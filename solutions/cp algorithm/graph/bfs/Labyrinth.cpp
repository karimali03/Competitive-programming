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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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

int di[]{1,-1,0,0};
int dj[]{0,0,1,-1};
char ch[]{'D','U','R','L'};

string bfs(vec<vec<char>> &v,int n,int m){
    vii vis(n,vi(m));
    queue<pair<int,int>>q;
    int sx,sy;
    f(i,0,n) f(j,0,m) if(v[i][j] == 'A') sx=i,sy=j;
    q.push({sx,sy});
    vis[sx][sy] = 1;
    vii par(n,vi(m,-1));
    while(!q.empty()){
        auto [x,y] = q.front(); q.pop();
        if(v[x][y] == 'B'){
            string res;
            while(v[x][y] != 'A'){
            //   cout<<par[x][y]<<" "<<x<<" "<<y<<endl;
               res.push_back(ch[par[x][y]]);
                x = x - di[par[x][y]];
                y = y - dj[par[x][y]];
            }
            return res;
        }
        for(int d = 0 ; d < 4 ; d++){
            int ni = x + di[d];
            int nj = y + dj[d];
            if(ni >= 0 && nj >= 0 && ni < n && nj < m && !vis[ni][nj] && v[ni][nj] != '#'){
                q.push({ni,nj});
                vis[ni][nj] = 1;
              //  cout<<ni<<" "<<nj<<" "<<d<<endl;
                par[ni][nj] = d;
            }
        }        
    }
    return {};
}

void solve(int test_case) {
    int n,m; cin>>n>>m;
    vec<vec<char>>v(n,vec<char>(m));
    f(i,0,n) f(j,0,m) cin>>v[i][j];
    auto res = bfs(v,n,m);
    if(res.empty()) cout<<"NO";
    else{
        cout<<"YES"<<ln;
        cout<<res.size()<<ln;
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