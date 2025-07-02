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


vector<int> kth_NGE(vector<int> &v , int k){
    int n = v.size();
    vector<int>res(n,-1);
    vector<stack<int>>st(k);
    for(int i = 0 ; i <  n ;i++){
        for(int j = k-1 ; j >= 0 ;j--){
            stack<int> cur;
            while(!st[j].empty() && v[st[j].top()] > v[i]){ // > for NSE
                cur.push(st[j].top()); 
                st[j].pop();
            }
            while(!cur.empty()){
                auto idx = cur.top(); cur.pop();
                if(j == k-1) res[idx] = i;
                else st[j+1].push(idx);
            }
        }
        st[0].push(i);
    }
    return res;
}

vector<int> kth_PGE(vector<int> & v , int k){
    int n = v.size();
    vector<int>res(n,-1);
    vector<stack<int>>st(k);
    for(int i = n-1 ; i >= 0 ;i--){
        for(int j = k-1 ; j >= 0 ;j--){
            stack<int> cur;
            while(!st[j].empty() && v[st[j].top()] > v[i]){ // > for NSE
                cur.push(st[j].top()); 
                st[j].pop();
            }
            while(!cur.empty()){
                auto idx = cur.top(); cur.pop();
                if(j == k-1) res[idx] = i;
                else st[j+1].push(idx);
            }
        }
        st[0].push(i);
    }
    return res;
}


void add(vi &res , int l , int r , int val){    
    if(l  > r || l < 0 || r >= res.size() ) return;
    res[l]+=val;
    if(r+1 < res.size()) res[r+1]-=val;
}
void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    auto ns = kth_NGE(v,1) , sns = kth_NGE(v,2);
    auto ps = kth_PGE(v,1) , sps = kth_PGE(v,2);
    vi res(n);
    for(int i = 0 ; i < n ; i++){
        int l = ps[i];
        int r = (ns[i] == -1 ? n : ns[i]);
      
        add(res , 0 , l-1 , v[i] * (i-l) * (r-i));
        add(res , r+1 , n-1 , v[i] * (i-l) * (r-i));
        add(res , l+1 , i-1 , v[i] * (i-l-1) * (r-i));
        add(res , i+1 , r-1 , v[i] * (i-l) * (r-i-1));
        int l2 = sps[i];
        int r2 = (sns[i] == -1 ? n : sns[i]);
        add(res , l , l , v[i] * (i - l2 - 1) * (r - i));
        add(res , r , r, v[i] * (i-l) * (r2-i - 1));
    }
    for(int i = 1 ; i < n ;i++) res[i]+=res[i-1];
    for(int i =0;i<n;i++) cout<<res[i]<<" ";
    cout<<ln;
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