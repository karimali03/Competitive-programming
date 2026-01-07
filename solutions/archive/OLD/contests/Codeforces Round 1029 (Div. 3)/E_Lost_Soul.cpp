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

void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n); cin>>a>>b;
    int mx = 0;
    multiset<int>st1,st2;
    int alt = 0;
    st1.insert(a.back());
    st2.insert(b.back());
    vi idx1(n+1,-1),idx2(n+1,-1);
    for(int i = n-1 ; i >= 0 ; i--){
        if(i&1){
            if(idx1[a[i]] == -1) idx1[a[i]] = i;
            if(idx2[b[i]] == -1) idx2[b[i]]=  i;
        }
        else{
            if(idx1[b[i]] == -1) idx1[b[i]] = i;
            if(idx2[a[i]] == -1) idx2[a[i]]=  i;
        }
    }
    for(int i = n-2; i  >= 0 ; i--){
       if((a[i] == b[i]) || (a[i] == a[i+1]) || (b[i] == b[i+1]) ) mx = max(mx,i+1);
       if(alt){
          // a st1   b st2
           if(st2.count(a[i]) || st1.count(b[i])  ||
             st2.count(b[i+1]) || st1.count(a[i+1]) ){
                mx = max(mx,i+1);
            }
                st2.erase(st2.find(a[i+1]));
                st1.erase(st1.find(b[i+1]));
            
            if(st1.count(a[i]) || st2.count(b[i]) ){
                mx = max(mx,i+1);
            }
            if(st1.count(b[i+1])){
                if(i&1){
                    if(idx1[b[i+1]] > i+2) mx = max(mx,i+1);
                }else{
                     if(idx2[b[i+1]] > i+2) mx = max(mx,i+1);
                }
            }
            if(st2.count(a[i+1])){
                if(i&1){
                    if(idx2[a[i+1]] > i+2) mx = max(mx,i+1);
                }else{
                     if(idx1[a[i+1]] > i+2) mx = max(mx,i+1);
                }
            }
            if(i+2 < n && (    st1.count(b[i+2]) || st2.count(a[i+2])   ))
            mx = max(mx,i+1);
            st2.insert(a[i+1]);
            st1.insert(b[i+1]);
       }
       else{
        // a st2  b st1
            if(st1.count(a[i]) || st2.count(b[i]) || st1.count(b[i+1]) ||
             st2.count(a[i+1]) ){
                mx = max(mx,i+1);
            }
            st1.erase(st1.find(a[i+1]));
            st2.erase(st2.find(b[i+1]));
            
            if(st2.count(a[i]) || st1.count(b[i]) ){
                mx = max(mx,i+1);
            }
            if(st2.count(b[i+1])){
                if(i&1){
                    if(idx1[b[i+1]] > i+2) mx = max(mx,i+1);
                }else{
                     if(idx2[b[i+1]] > i+2) mx = max(mx,i+1);
                }
            }
            if(st1.count(a[i+1])){
                if(i&1){
                    if(idx2[a[i+1]] > i+2) mx = max(mx,i+1);
                }else{
                     if(idx1[a[i+1]] > i+2) mx = max(mx,i+1);
                }
            }
            if(i+2 < n && (    st2.count(b[i+2]) || st1.count(a[i+2])   ))
            mx = max(mx,i+1);
            st1.insert(a[i+1]);
            st2.insert(b[i+1]);
        
        }
            alt = 1-alt;
            if(alt){
                st1.insert(b[i]);
                st2.insert(a[i]);
            }else{
                    st1.insert(a[i]);
                    st2.insert(b[i]);
            }
    }

    cout<<mx<<ln;
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