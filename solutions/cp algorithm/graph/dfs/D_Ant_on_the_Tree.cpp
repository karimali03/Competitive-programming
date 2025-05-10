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

vi order;
pair<vi,int> dfs(vii & adj,int node,int par){
    vector<pair<int,vi>>v;
    int leaf = node;
    for(auto it : adj[node]){
        if(it == par) continue;
        auto cur = dfs(adj,it,node);
        leaf = cur.second;
        v.push_back({order[cur.second],cur.first});
    }
    sort(all(v));
    vi ret = {node};
    for(auto it : v){
        for(auto c : it.second) ret.push_back(c);
        ret.push_back(node);
    }
  
    return {ret , leaf};
}
void solve(int test_case) {
    int n; cin>>n;
    order = vi(n,-1);
    vii v(n);
    f(i,0,n-1){
        int x,y; cin>>x>>y; x--,y--;
        v[x].push_back(y);
        v[y].push_back(x);
    }   
    string line;
    getline(cin,line);  getline(cin, line);
    stringstream ss(line);
    int num;
    vector<int> numbers;
    while (ss >> num) {
        numbers.push_back(num); 
    }
    for(int i = 0 ; i <  numbers.size() ; i++){
        order[numbers[i]-1] = i;
    }

    auto res = dfs(v,0,-1);
    int cur = 0;


    for(int i = 0 ; i < res.first.size() ; i++){
        if(order[res.first[i]] == -1) continue;
        if(order[res.first[i]] != cur) return void(cout<<-1<<ln);
        cur++;
    }
    for(auto it : res.first) cout<<it+1<<" ";
    

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