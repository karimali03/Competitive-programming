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


int bfs(map<int,vi> &X,map<int,vi>& Y,int n,int m){
    map<tuple<int,int,int>,int>d;
    priority_queue<tuple<int,int,int>,vec<tuple<int,int,int>>,greater<>> q;
    d[{0,1,1}] = 0;
    q.push({0,1,1});
    while (!q.empty()) {
        auto [ty,x,y] = q.top(); q.pop();
        for(auto pos : {1,-1}){
            for(auto it :  Y[y+pos]){
                int w = ((it == x || ty) ? 0 : 1);
                if(!d.count({w,it,y+pos}) || (d[{w,it,y+pos}] > w+d[{ty,x,y}]) ){
                        d[{w,it,y+pos}] = w + d[{ty,x,y}];
                        if(w) q.push({w,it,y+pos});
                        else q.push({w,it,y+pos});
                }
            }
        }

        for(auto pos : {1,-1}){
            for(auto it :  X[x+pos]){
                int w = ((it == y || ty) ? 0 : 1);
                if(!d.count({w,x+pos,it}) || (d[{w,x+pos,it}] > w+d[{ty,x,y}]) ){
                    d[{w,x+pos,it}] = w + d[{ty,x,y}];
                    if(w) q.push({w,x+pos,it});
                    else q.push({w,x+pos,it});
                }
            }
        }
    }

 
    for(auto it : X[n-1]){
        for(auto a : {0,1}){
            if(!d.count({n,m}) || d[{n,m}] > 1+d[{n-1,it}]){
                d[{n,m}] = 1 + d[{n-1,it}];
            }
        }
    }
    for(auto it : Y[m-1]){
        if(!d.count({n,m}) || d[{n,m}] > 1+d[{it,m-1}]){
            d[{n,m}] = 1 + d[{it,m-1}];
        }  
    }
    for(auto it : X[n]){
        if(!d.count({n,m}) || d[{n,m}] > 1+d[{n,it}]){
            d[{n,m}] = 1 + d[{n,it}];
        }  
    }
    for(auto it : Y[m]){
        if(!d.count({n,m}) || d[{n,m}] > 1+d[{it,m}]){
            d[{n,m}] = 1 + d[{it,m}];
        }
    }
    return (d.count({n,m}) ? d[{n,m}] : -1);
}

void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    map<int,vi>Xaxis,Yaxis;
    f(i,0,k){
        int x,y; cin>>x>>y;
        Xaxis[x].push_back(y);
        Yaxis[y].push_back(x);
    }
    cout<<bfs(Xaxis,Yaxis,n,m)<<ln;
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