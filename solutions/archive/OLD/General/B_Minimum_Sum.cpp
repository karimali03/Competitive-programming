#include <bits/stdc++.h>
#include <random>
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

vector<int> NGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,-1);
    for(int i = 0 ; i < n ; i++){
        while(!st.empty() && v[st.top()] > v[i]){ // > for NSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> PGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,-1);
    for(int i = n-1 ; i >= 0 ; i--){
        while(!st.empty() && v[st.top()] > v[i]){ // > for PSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}


vector<int> kth_NGE(vector<int> &v , int k){
    int n = v.size();
    vector<int>res(n,-1);
    vector<stack<int>>st(k);
    for(int i = 0 ; i <  n ;i++){
        for(int j = k-1 ; j >= 0 ;j--){
            stack<int> cur;
            while(!st[j].empty() && v[st[j].top()] < v[i]){ // > for NSE
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
            while(!st[j].empty() && v[st[j].top()] < v[i]){ // > for NSE
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




void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    auto pg = PGE(v);
    auto ng = NGE(v);
    int res = 0;
    for(int i = 0; i < n ; i++){
        int l = pg[i];
        int r = (ng[i] == -1 ? n : ng[i]);
      //  cout<<l<<" "<<r<<" "<<abs(l-i)<<" "<<abs(r-i)<<ln;
        res += v[i] * (abs(l-i) * abs(r-i));
    }
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}