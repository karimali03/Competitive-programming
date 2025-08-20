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





struct dsu {
    vector<int> size, par , time;
    int cc;

    dsu(int n) : cc(n) , size(n + 1, 0), par(n + 1) , time(n+1,-1) {
        for (int i = 0; i <= n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        int pr = par[x];
        par[x] = get(par[x]);
        if(time[x] == -1) time[x] = time[pr];
        if(pr != par[x]){
            if(time[x] == -1) time[x] = time[par[x]];
        }
        return par[x];
    }

    bool merge(int x, int y , int t) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        int pr = get(1);
        if(x == pr && y != pr) par[y] = x , time[y] = t;
        else{
            if(y == pr && x != pr) time[x] = t;
            par[x] = y;
        } 
        cc--;
        return true;
    }



};



void solve(int test_case) {
    int n,m; cin>>n>>m;
    vii v(n+1,vi(2));
    vii vis(n+1,vi(2));
   for(int i = 1 ; i <= n ; i++){
        cin>>v[i][0]>>v[i][1];
    }
    vii q(m,vi(2));
    f(i,0,m){
        cin>>q[i][0]>>q[i][1];  q[i][1]--;
        vis[q[i][0]][q[i][1]] = 1;
    }

  

    dsu st(n);
    for(int i = 1 ; i <= n ; i++){
        if(!vis[i][0] && v[i][0] != -1){
            st.merge(i,v[i][0],-1);
        }
        if(!vis[i][1] && v[i][1] != -1){
            st.merge(i,v[i][1],-1);
        }
    }


    for(int i = m-1 ; i >= 0 ; i--){
        if(v[q[i][0]][q[i][1]] != -1){
            st.merge(q[i][0],v[q[i][0]][q[i][1]],i);
        }
    }

    for(int i = 1 ; i <= n ; i++){
        st.get(i);
        cout<<st.time[i]<<ln;
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