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

const int SQ = 320;
void calc(vi &v,int n,int k){
    for(int i = 0 ;i < n ; i ++){
        if(v[i]%(k+1)) v[i] = 1;
        else v[i] = 0;
    }
}
void solve(int test_case) {
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    vi pre(n),suf(n);
    calc(v,n,k);
    int cnt = count(all(v),1);
  
    vi res(n+1);
    if(cnt < SQ ){
        vi l(n),r(n);
        for(int i = 0 ; i < n ; i++){
            while( i < n && v[i] == 1) i++;
            if(i <  n){
                int c = 0;
                int st = i;
                while(i < n && v[i] == 0) c++,i++;
                if(st-1 >= 0) r[st-1]+=c;
                if(i < n) l[i]+=c;
            }
        }
        vi idx;
        for(int i = 0 ;i  < n ;i++) if(v[i]) idx.push_back(i);
        for(int i = 1 ; i <= n ; i++){
            for(int c = 0 ; c < idx.size() ; c++){
                if(c+i-1 < idx.size()){
                    int a = idx[c];
                    int b = idx[c+i-1];
                    int prv = l[a];
                    int nxt = r[b];
                    res[i] += (prv+1)*(nxt+1);
                }
            }
        }
    }
    else{
        pre[0] = (v[0]==1);
        for(int i = 1 ; i < n ; i++) pre[i]=pre[i-1]+(v[i]==1);
        suf[0] = (v[n-1]==1);
        for(int i=n-2;i>=0;i--) suf[i]=suf[i+1]+(v[i]==1);
        vector<pair<int,int>>zero;
        
        for(int i = 0 ; i < n ; i++){
            while( i < n && v[i] == 1) i++;
            if(i <  n){
                int c = 0;
                int st = i;
                while(i < n && v[i] == 0) c++,i++;
                zero.push_back({st,c});
            }
        }
        for(int i = 1 ; i  <= n ; i++){
            res[i] = cnt-i+1;
        }
        for(int i = 0 ;i <  n; i++){
            if(v[i]) continue;
            for(int j = i+1 ; j < n ; j++){
                res[pre[j]-pre[i]]++;
            }
        }
        for(int i = n - 1; i >= 0 ; i--){
            if(v[i]) continue;
            for(int j = i-1 ; j >= 0 ; j--){
                if(!v[j]) continue;
                res[suf[j]-suf[i]]++;
            }
        }
    }
    for(int i=1;i<=n;i++) cout<<res[i]<<" ";
    cout<<ln;
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