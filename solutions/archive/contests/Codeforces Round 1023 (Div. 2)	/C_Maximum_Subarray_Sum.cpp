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


int mxSub(vector<int>& v, int l, int r) {
    if( l > r || l == -1) return 0;
    int mx = LLONG_MIN, sum = 0;

    for (int i = l; i <= r; i++) {
        sum += v[i];
        mx = max(mx, sum);
        if (sum < 0) sum = 0;
    }

    return mx;
}

void solve(int test_case) {
    int n,k; cin>>n>>k;
    string s; cin>>s;
    vi v(n); cin>>v;
    int l = 0,r = 0;
    vii in;
    for(int i = 0 ; i < n+1 ; i++){
        if( i == n || s[i] == '0' ){
            if( l != -1) in.push_back({l,r});
            if(mxSub(v,l,r) > k){ 
                return void(cout<<"No"<<ln);
            }
            l = -1;
            continue;
        }
        if(s[i] == '1'){
            r =  i;
            if(l == -1) l = i;
        }
    }
    int c = count(all(s),'0');
    if(c == 0){
        if(mxSub(v,0,n-1) == k){
            cout<<"Yes"<<ln;
            f(i,0,n) cout<<v[i]<<" ";
            cout<<ln;
        }
        else cout<<"No"<<ln;
        return;
    }
    if(in.size() == 0){
        cout<<"Yes"<<ln;
        cout<<k<<" ";
        for(int i = 1 ; i < n ; i++) cout<<0<<" ";
        cout<<ln;
    }
    if(in.size() == 1){
        int sum = 0;
        bool fs = true;
        
        if(in[0][0]-1 >= 0){
            int mx2 = 0; int sm = 0;
            for(int x = in[0][0] ; x <= in[0][1] ; x++) {
                sm+=v[x];
                mx2 = max(mx2,sm);
            }
            sum = mx2;
        }
        else{
            int mx1 = 0; int sm = 0;
            for(int x = in[0][1] ; x >= in[0][0] ; x--) {
                sm+=v[x];
                mx1 = max(mx1,sm);
            }
            sum = mx1;
        }
        cout<<"Yes"<<ln;
        for(int i = 0  ;i <  n; i++){
            if(s[i] == '0'){
                if(fs){
                    cout<<k-sum<<" ";
                    fs = false;
                }
                else cout<<0<<" ";
            }
            else cout<<v[i]<<" ";
        }
        cout<<ln;
    }
    else {
        bool fs = true;
        int mx1 = 0;
        int mx2 = 0;
        int sm = 0;
        for(int x = in[0][1] ; x >= in[0][0] ; x--) {
            sm+=v[x];
            mx1 = max(mx1,sm);
        }
        sm = 0;
        for(int x = in[1][0] ; x <= in[1][1] ; x++) {
            sm+=v[x];
            mx2 = max(mx2,sm);
        }
        int sum = mx1+mx2;
        cout<<"Yes"<<ln;
        for(int i = 0 ; i < n ; i++){
            if(s[i] != '0') cout<<v[i]<<" ";
            else if(i < in[0][0] || i > in[1][1]) cout<<-100000000000000000<<" ";
            else{
                if(fs){
                    cout<<k-sum<<" ";
                    fs = false;
                }
                else cout<<0<<" ";
            }
        }
        cout<<ln;
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