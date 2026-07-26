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


int count_submasks(int num, int n) {
    int ans = 0;
    bool match = true;
 
    for (int i = 30; i >= 0; i--) {
        int v_bit = (num >> i) & 1;
        int k_bit = (n >> i) & 1;
        int p = __builtin_popcount(num & ((1 << i) - 1));
 
        if (v_bit == 0) {
            if (k_bit == 1) {
                ans += (1 << p);
                match = false;
                break;
            }
        }
        else
            if (k_bit == 1)
                ans += (1LL << p);
    }
 
    return ans + (match != 0);
}


void solve(int test_case) {
    int l,r,x; cin>>l>>r>>x;
    int mx = count_submasks(x,r) - count_submasks(x,l-1);
    for(int i = 0;i < 30 ; i++){
        if((x>>i)&1){
            int num = (x ^ (1<<i)) | ((1<<i)-1);
            mx = max(mx ,count_submasks(num,r) - count_submasks(num,l-1));
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