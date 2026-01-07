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


mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rand_range(ll l, ll r) { return l + (ull) rng() % (r - l + 1); }
void shuffle(vector<int> &v) { shuffle(v.begin(), v.end(), rng); }
char rand_char() { return 'a' + rand_range(0, 25); }



bool getBit(int num, int i) {
    return ((num & (1ll<< i)) != 0);  
}

int setBit(int num, int i) {
    return num |(1ll << i); }

int clearBit(int num, int i) {
    int mask =~(1ll << i);
    return num & mask;  
}

int calc(int n,int x){
     if(n == x){
        return x;
    }
    bool eq = false;
    int last = 0;
    for(int i = 0 ; i < 64 ; i++){
        if(getBit(x,i) && !getBit(n,i)){
            return -1;
        }
        if(!getBit(x,i) && getBit(n,i)){
            last = i;
            if(eq) {
                return -1;
            }
        }
        if(getBit(x,i) && getBit(n,i)) eq = true;
    }

    if(x == 0){
        for(int i = 0 ; i < 64 ; i++) if(getBit(n,i)) last = i;
    }
    for(int i = 0 ;i <= last ; i++) n = clearBit(n,i);
    n |= (1ll<<(last+1));
    return n;
}
void srh(){
    for(int i = 1 ; i <= 100 ; i++){
        int cur = i;
        int prv = cur;
        for(int j = i+1 ; j <= 100 ; j++){
            cur &=j;
            int ret = calc(i,cur);
            cout<<ret<<" "<<j<<" "<<cur<<" "<<prv<<ln;
            prv = cur;
        }
    }
}

void solve(int test_case) {
    int n,x; cin>>n>>x;
    if(n == x){
        cout<<x<<ln;
        return;
    }
    bool eq = false;
    int last = 0;
    for(int i = 0 ; i < 64 ; i++){
        if(getBit(x,i) && !getBit(n,i)){
            NA; return;
        }
        if(!getBit(x,i) && getBit(n,i)){
            last = i;
            if(eq) {
                NA; return;
            }
        }
        if(getBit(x,i) && getBit(n,i)) eq = true;
    }

    if(x == 0){
        for(int i = 0 ; i < 64 ; i++) if(getBit(n,i)) last = i;
    }
    for(int i = 0 ;i <= last ; i++) n = clearBit(n,i);
    n |= (1ll<<(last+1));
    cout<<n<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    srh();
    for (int i = 1; i <= t; i++) {
       // solve(i);
    }

    return 0;
}