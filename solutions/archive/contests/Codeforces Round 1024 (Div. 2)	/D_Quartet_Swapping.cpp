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

int countInversions(vi &v,int l,int r){
    if(l >= r) return 0;
    int mid = (l+r)/2;
    int res = countInversions(v,l,mid) + countInversions(v,mid+1,r);
    vi x(r-l+1);
    int i = l , j = mid+1 , k = 0;
    while(i <= mid && j <= r){
        if(v[i] <= v[j]){
            res+=(j-mid-1);
            x[k++] = v[i++];
        }
        else x[k++] = v[j++];
    }
    while(i <= mid){
        res+=(j-mid-1);
        x[k++] = v[i++];
    }
    while(j <= r){
        x[k++] = v[j++];
    }
    for(int i = l ; i <= r ; i++) v[i] = x[i-l];
    return res;
}


void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vi res1,res2;
    f(i,0,n){
        if(i&1) res2.push_back(v[i]);
        else res1.push_back(v[i]);
    }
    int inv1 = countInversions(v,0,n-1);
    sort(all(res1)); sort(all(res2));
    vi res;
    for(int i = 0 ; i <= n/2 ; i++){
        if(i < res1.size()) res.push_back(res1[i]);
        if(i < res2.size()) res.push_back(res2[i]);
    }
    vi r = res;
    int inv2 = countInversions(r,0,n-1);
    if((inv1%2) != (inv2%2) ) swap(res[n-1],res[n-3]);
    f(i,0,n) cout<<res[i]<<" ";
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