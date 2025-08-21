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


int dx[] = {2,2,-2,-2,1,-1,1,-1};
int dy[] = {1,-1,1,-1,2,2,-2,-2};
void solve(int test_case) {
    int n,k; cin>>n>>k;
    vii vis(n+1,vi(n+1,-1));
    vector<pair<int,int>>pr(k); 
    for(int i = 0 ; i < k ; i++){
        int x,y; cin>>x>>y;
        vis[x][y] = i;
        pr[i] = {x,y};
    }
    set<pair<int,int>>st;
    vector<int>c(k);
    for(int i = 0 ; i < k ; i++){
        int cnt = 0;
        for(int d = 0 ; d < 8 ; d++){
            int ni = pr[i].first + dx[d];
            int nj = pr[i].second + dy[d];
            if(ni > 0 && nj > 0 && ni <= n && nj <= n && vis[ni][nj] != -1)
             cnt++;
        }
        if(cnt){
            st.insert({cnt,i});
            c[i] = cnt;
        }
    }
    int res = 0;
    while(!st.empty()){
        auto it = *st.rbegin();
        st.erase(st.find(it));
        int i = it.second;
        res++; 
        vis[pr[i].first][pr[i].second] = -1;
         for(int d = 0 ; d < 8 ; d++){
            int ni = pr[i].first + dx[d];
            int nj = pr[i].second + dy[d];
            if(ni > 0 && nj > 0 && ni <= n && nj <= n && vis[ni][nj] != -1){
                int idx = vis[ni][nj];
                st.erase(st.find({c[idx],idx}));
                c[idx]--;
                if(c[idx]) st.insert({c[idx],idx});
            }
        }
    }
    cout<<res<<ln;

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