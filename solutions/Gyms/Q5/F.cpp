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

int n,k,c;
vi primes;
map<int,int>mem;
const int INF =2e18;
int bt(int x){
    if(x == 1) return 0;
    if(mem.count(x)) return mem[x];
    // go to 1 direct x-1 ops * c
    int ret = 0;
    if(INF / c < x-1) ret = INF;
    else ret = c * (x-1);
    // go to nearst multiple of pi and diivde by pi
    for(auto &it : primes){
        if(it > x) break;
        int nw = (x - (x%it)) / it;
        ret = min(ret , (x%it) * c + bt(nw));
    }
    return mem[x] = ret;
}
void solve(int test_case) {
    cin>>n>>k>>c;
    primes = vi(k);
    for(int i =0 ;i < k; i++) cin>>primes[i];
    sort(all(primes));
    cout<<bt(n)<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
         solve(i);
    }

    return 0;
}