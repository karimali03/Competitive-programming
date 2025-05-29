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





vii cnt1(300005,vi(2)),cnt2(300005,vi(2));
bool valid(int A,int B,int it,int x){
    int bj = B - it;
    if(abs(bj) > 200005) return false;
    int found = cnt2[abs(bj)][(bj<0 ? 1: 0)];
    if( !found || (A*B-bj*A)%(B-bj) != 0) return false;
    int ai = (A*B-bj*A)/(B-bj) - (x / (it));
     if(abs(ai) > 200005) return false;
    found = cnt1[abs(ai)][(ai<0 ? 1: 0)];
    if(!found) return false;
    return true;
}

void solve(int test_case) {
    int n,m,q; cin>>n>>m>>q;
    vi a(n),b(m); cin>>a>>b;

    int A = 0,B = 0;
    f(i,0,n){
        A+=a[i];
        if(a[i] < 0) cnt1[abs(a[i])][1] = 1;
        else cnt1[abs(a[i])][0] = 1;
    }  
    f(i,0,m){
          B+=b[i];
        if(b[i] < 0) cnt2[abs(b[i])][1] = 1;
        else cnt2[abs(b[i])][0] = 1;
    }
    
    while(q--){
        int x; cin>>x;
      
        bool dd = true;
        for(int i=1;i*i<=abs(x);i++){
            if(abs(x)%i==0){
                if(valid(A,B,i,x) || valid(A,B,-i,x)){
                    YES; 
      
                    dd = false;
                    break;
                }
                if(i!=abs(x)/i){
                    if(valid(A,B,abs(x)/i,x) || valid(A,B,-(abs(x)/i),x)){
                        YES; dd = false;
                     
                        break;
                    }      
                }
            }
        }
        if(dd) cout<<"NO\n";
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