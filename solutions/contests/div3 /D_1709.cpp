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

vector<int> srt(vi &v,int n){
    vi vv = v;
    sort(all(vv));
    vi op;
    for(int i = 0 ; i <  n ;i++){
        if(v[i] == vv[i]) continue;
        int idx = 0;
        for(int j = 0 ; j <  n ;j++) if(v[j] == vv[i]){
            idx = j;break;
        }
        if(idx > i){
            while(idx != i){
                op.push_back(idx-1);
                swap(v[idx-1],v[idx]);
                idx--; 
            }
        }else{
            while(idx != i){
                op.push_back(idx);
                swap(v[idx],v[idx+1]);
                idx++;
            }
        }
    }
    return op;
}

void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n); cin>>a>>b;
    vi op1 = srt(a,n);
    vi op2 = srt(b,n);
    vi op3;
   
    for(int  i = 0 ;i < n ; i++){
        if(a[i] > b[i]) op3.push_back(i);
    }
    int k = op1.size() + op2.size() + op3.size();
    cout<<k<<ln;
    for(auto it : op1){
        cout<<1<<" "<<it+1<<ln;
    }
    for(auto it : op2){
        cout<<2<<" "<<it+1<<ln;
    }
    for(auto it : op3){
        cout<<3<<" "<<it+1<<ln;
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