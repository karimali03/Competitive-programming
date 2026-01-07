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


int topo_sort(vector<vector<int>> &adj) {	// O( E+V )
            int sz = adj.size();
            vector<int> indegree(sz, 0);	
            for (int i = 0; i < sz; ++i)
                for (int j : adj[i])
                indegree[j]++;
                    
            queue<int>ready;	
            vector<int>cnt(sz);
            vector<set<int>>st(sz);
            vector<bool>valid(sz,true);
            for (int i = 0; i < sz; ++i)  
            if (indegree[i] == 1){
                ready.push(i);
                st[i].insert(0);
            } 
            int res = sz-1;
            int node = -1;
            vi vis(sz);
            while (!ready.empty()) {
                    auto cur = ready.front();  ready.pop();
                    vis[cur] = 1;
                    node = cur;
                    if(st[cur].size() > 1) valid[cur] = false;
                    else cnt[cur] = 1 + *st[cur].begin();
                    for (int j : adj[cur]){
                        if (--indegree[j] == 1)	{                     
                            ready.push(j);
                        }
                        if(vis[j]) continue;
                        if(!valid[cur]) valid[j] = false;
                        {
                            if(st[j].count(cnt[cur])) res-=cnt[cur];
                            else st[j].insert(cnt[cur]);
                        }
                    }	
            }	
           
            if(st[node].size() <= 2){
                for(auto it : adj[node]){
                    if(!valid[it]) return -1;
                }
                return res;
            }
            return -1;
}

void solve(int test_case) {
    int n; cin>>n;
    vii adj(n);
    f(i,0,n-1){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int ans = topo_sort(adj);
    cout<<ans<<ln;

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