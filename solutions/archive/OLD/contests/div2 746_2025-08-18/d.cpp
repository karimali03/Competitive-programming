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

int ask(int l,int r,vi &rng){
    cout<<"? ";
    set<int>st;
    for(int i = l ; i <= r ; i++) st.insert(rng[i]+1);
    cout<<st.size()<<" ";
    for(auto it : st) cout<<it<<" ";
    cout<<endl;
    cout.flush();
    int ret; cin>>ret;
    return ret;
}
void answer(int a,int b){
    cout<<"! "<<a<<" "<<b<<endl;
    return;
}

void solve(int test_case) {
    int n; cin>>n;
    vector<vector<int>>adj(n);
    vector<int>cur;
    for(int i = 0 ;i  < n-1 ; i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    function<void(int,int)> dfs = [&](int x,int p) -> void{
        for(auto it : adj[x]){
            if(it == p) continue;
            cur.push_back(x);
            cur.push_back(it);
            dfs(it,x);            
        }
        if(p != -1){
            cur.push_back(x); cur.push_back(p);
        }
    };
    dfs(0,-1);
    int sz = cur.size();
    int mx = ask(0,sz-1,cur);

    function<void(int,int)> ans = [&](int l,int r) -> void{
        int mid = l + (r-l)/2;
        auto res = ask(l,mid,cur);
        if(res == mx){
            set<int>st;
            for(int i = l ; i <= mid ; i++) st.insert(cur[i]+1);
            if(st.size() == 2){
                answer(*st.begin(),*(next(st.begin())));
                return;
            }
            ans(l,mid);
        }
        else{
            set<int>st;
            for(int i = mid ; i <= r ; i++) st.insert(cur[i]+1);
            if(st.size() == 2){
                answer(*st.begin(),*(next(st.begin())));
                return;
            }
            ans(mid,r);
        }
    };
    ans(0,sz-1);
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