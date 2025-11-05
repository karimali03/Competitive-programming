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

const int M1 = 1e9 + 9;
const int M2 = 1e9 + 7;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll BASE1 = uniform_int_distribution<ll>(100000000, 1000000000)(rng) | 1; // random odd base
ll BASE2 = uniform_int_distribution<ll>(100000000, 1000000000)(rng) | 1; // random odd base

map<pair<int,int>,pair<int,int>> hval;
int cnt = 1;
const int N = 4005;
int pow1[N],pow2[N];
void init(){
    pow1[0] = pow2[0] = 1;
    for(int i = 1 ; i < N ; i++){
        (pow1[i] = pow1[i-1] * BASE1)%=M1;
        (pow2[i] = pow1[i-1] * BASE2)%=M2;
    }
}

pair<int,int> get(pair<int,int> x) {
    if (hval.count(x)) return hval[x];
    hval[x] = {pow1[cnt] , pow2[cnt]}; cnt++;
    return hval[x];
}

struct MultisetHashing {
    vector<pair<int,int>> h;
    int n;
    MultisetHashing(vector<pair<int,int>> &v) {
        n = v.size();
        h = vector<pair<int,int>>(n + 1);
        for (int i = 0; i < n; i++) {
            auto it = get(v[i]);
            (h[i+1].first = h[i].first + it.first)%=M1;
            (h[i+1].second = h[i].second + it.second)%=M2;
        }
    }
    // zero based
    pair<int,int> get_hash(int l, int r) {
        pair<int,int> ret = { (h[r+1].first-h[l].first+M1)%M1, (h[r+1].second-h[l].second+M1)%M1 };
        return ret;
    }
};


void solve(int test_case) {
    int n; cin>>n;
    vector<pair<int,int>>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i].first>>v[i].second;
        if(v[i].first > v[i].second) swap(v[i].first,v[i].second);
    }
    MultisetHashing sh(v);
    map<pair<int,int>,int>mp;
    for(int i = 0;i < n ; i++){
        for(int j = i; j < n ; j++){
            cout<<i<<" "<<j<<" "<<sh.get_hash(i,j).first<<ln;
            mp[sh.get_hash(i,j)]++;
        }
    }
    int res = 0;
    for(auto &[a,b] : mp) cout<<a.first<<" "<<b<<ln;
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}