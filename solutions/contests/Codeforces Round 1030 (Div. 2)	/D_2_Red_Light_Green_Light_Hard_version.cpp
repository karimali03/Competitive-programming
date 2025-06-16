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

const int N = 200005;
int d[N];
int n,k,q;

int nxt[2*N];
int state[2*N]; 
bool cycle[2*N];

void init(int n){         
    f(i,0,n*2) nxt[i]=-1,state[i]=0,cycle[i]=false;
}

bool dfs(int u){
    if(state[u] == 1) return cycle[u] = true;
    if(state[u] == 2) return cycle[u];
    state[u] = 1;
    if(nxt[u] != -1) cycle[u] = dfs(nxt[u]);
    else cycle[u] = false;
    state[u] = 2;
    return cycle[u];
}

void solve(int test_case) {
    cin>>n>>k;
    init(n);
    vi p(n); cin>>p;
    f(i,0,n) cin>>d[i];
    map<int,vi>R,L;
    for(int i = 0 ; i < n ; i++){
        int gr = (p[i]%k-d[i]%k+k)%k;
        int gl = (p[i]%k+d[i]%k)%k;
        R[gr].push_back(i);
        L[gl].push_back(i);
    }
   

    for(int i = 0 ; i < n ;i++){
        int gr = (p[i]%k-d[i]%k+k)%k;
        int gl = (p[i]%k+d[i]%k)%k;
       
        auto it = lower_bound(all(L[gl]),i);
        if(it != L[gl].begin()) nxt[i*2] = *(prev(it))*2+1;
        it = lower_bound(all(R[gr]),i);
        if(next(it) != R[gr].end()) nxt[i*2+1] = *(next(it))*2;
   
    }

    for(int i = 0 ; i < 2*n ; i++){
        if(!state[i]) dfs(i);
    }
   

    cin>>q;
    while(q--){
        int x; cin>>x;
        auto it = lower_bound(all(p),x) - p.begin();
        if(it == n){
            YES; continue;
        }
        int gr = x%k;
    
        if(!R.count(gr)){
            YES; continue;
        }
        auto itt = lower_bound(all(R[gr]),it);
        if(itt == R[gr].end()) YES;
        else if(dfs((*itt)*2)) NO;
        else YES;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}