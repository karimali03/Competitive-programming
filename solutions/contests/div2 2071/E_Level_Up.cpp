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


struct query{
    int idx,k,qi;
    query(int idx = -1,int k = -1,int i = -1):idx(idx),k(k),qi(i){};
    bool operator<(query &rhs){
        return k > rhs.k;
    }
};
const int N = 200005;
query x[N];
int v[N];
int n,q;
const int SQ = 500;
bool low[SQ][N];
int lvl[N];
bool res[N];

void solve(int test_case) {
    cin>>n>>q;
    f(i,0,n) cin>>v[i];
    f(i,0,q){
        int idx,k; cin>>idx>>k; idx--;
        x[i] = query(idx,k,i);
    }
    sort(x,x+q);
    
    for(int i = 1 ; i < SQ ; i++){
            int lvl = 1 ,cnt = 0;
            for(int j = 0 ; j < n ; j++){
                if(v[j] >= lvl) cnt++,low[i][j] =true;
                if(cnt == i){
                    lvl++; cnt=0;
                }
            }
    }


    vector<deque<int>>a;
    a.push_back(deque<int>());
    for(int i = 0;i< n ; i++) a[0].push_back(i),lvl[i]=1;
    int cur = n;
    
    for(int i = 0 ; i < q ; i++){
        if(x[i].k < SQ){
            res[x[i].qi] = low[x[i].k][x[i].idx];
            continue;
        }
        int k = x[i].k;
       
        if(cur > k){
            for(int j = 0 ; j  < a.size() ; j++){
            
                while(a[j].size() > k){
                    int idx = a[j].back(); a[j].pop_back();
                    if(v[idx] >= j+2){
                        if(j+1 == a.size()) a.push_back(deque<int>());
                        a[j+1].push_front(idx);
                        lvl[idx] = j+2;
                    }
                    else lvl[idx] = 1'000'000;
                }
            }
        }
        cur = k;
        if(v[x[i].idx] >= lvl[x[i].idx]) res[x[i].qi] = true;
        else res[x[i].qi] = false;
    }

    for(int i = 0 ; i < q ; i++){
        cout<<(res[i]?"YES\n":"NO\n");
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