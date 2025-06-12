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

int n;
const int N = 10005;
const int X = 1000005;
int a[N],b[N];
int cnt[X]{};
//  sum a = sum b +  k * c
bool valid(int k){
    for(int i  = 0; i  < n ;i++){
        int val = a[i] % k;
        if(cnt[val] == 0){
            for(int j = 0  ; j < i ; j++) cnt[a[j]%k]++; 
            return false;
        } 
        cnt[val]--;
    }
    return true;
}

void solve(int test_case) {
    cin>>n;
    f(i,0,n) cin>>a[i];
    f(i,0,n) cin>>b[i];
    sort(a,a+n); sort(b,b+n);
    bool eq = true;
    for(int i = 0 ; i  < n; i++){
        eq&=(a[i]==b[i]);
    }    
    if(eq){
        cout<<10000000<<ln;
        return;
    }
    int sum =0 ;
    for(int i = 0 ; i < n ; i++){
        sum = sum + a[i] - b[i];
    }
    if(sum <= 0 ){
        cout<<-1<<ln;
        return;
    }
    for(int i = 0 ; i < n ; i++) cnt[b[i]]++;
    for(int i  = 1 ; i <= sum && i*i <= sum ; i++){
        if(sum % i) continue;
        if(valid(i)){
            cout<<i<<ln;
            return;
        }
        if(valid(sum/i)){
            cout<<sum/i<<ln;
            return;
        }
    }
    cout<<-1<<ln;
    for(int i = 0 ; i < n ; i++) cnt[b[i]] = 0;
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