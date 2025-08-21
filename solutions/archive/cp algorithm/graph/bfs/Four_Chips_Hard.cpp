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


int vis[71][71][71][71]{};

bool isvalid(vi &v ){
    sort(all(v));
    for(int i = 0 ; i < 4 ; i++){
        if(v[i] <= 0 || v[i] > 70) return false;
        if(i && v[i] == v[i-1]) return false;
    }
    if(vis[v[0]][v[1]][v[2]][v[3]]) return false;
    vis[v[0]][v[1]][v[2]][v[3]] = 1;
    return true;
}

void solve(int test_case) {
//    debug("-----");
   vi v(4); cin>>v;
   vi init {1,2,3,4};
   queue<vi>q;

   q.push(init);
   memset(vis,0,sizeof(vis));
   vis[1][2][3][4] = 1;

   int lvl = 0;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto x = q.front(); q.pop();
            // debug(x);
            // debug(v);
            // debug(lvl);
            if(x == v) return void(cout<<lvl<<"\n");
            for(int i = 0 ; i < 4 ; i++){
                vi xx = x; xx[i]++;
                if(isvalid(xx)) q.push(xx);
                
                xx = x; xx[i]--;
                if(isvalid(xx)) q.push(xx);
        
                for(int j = 0 ; j < 4 ; j++){
                    if(i == j) continue;
                    xx = x;
                    int dis = xx[j] - xx[i];
                    xx[i]+=dis*2;
                    if(isvalid(xx)) q.push(xx);
                    // if(xx[i] == 2 && xx[j] == 4){
                    //     debug(xx[i]);
                    //     debug(xx[j]);
                    //     debug(dis);
                    //     debug(xx); debug(lvl);
                    // }
                    
                }

    
            }
        }
        lvl++;
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