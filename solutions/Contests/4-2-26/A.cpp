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

ll power(ll base, ll exp) {
    ll res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res *= base;
        base *= base;
        exp /= 2;
    }
    return res;
}

int sumDigitsFrom1ToN(int n) {
    if (n <= 0) return 0;
    if (n < 10) return n * (n + 1) / 2;
    
    string s = to_string(n);
    int d = s.length() - 1;
    ll p = power(10, d);
    ll msd = n / p;
    ll rem = n % p;
    ll term1 = msd * 45 * d * (p / 10);
    ll term2 = (msd * (msd - 1) / 2) * p;
    ll term3 = msd * (rem + 1);
    
    return term1 + term2 + term3 + sumDigitsFrom1ToN(rem);
}


int calc(int n) {
    int ret = 0;
    int len = 1;
    ll st = 1; 
    while (true) {
        ll next_st = st * 10;
        if (n < next_st) {
            ret += (n - st + 1) * len;
            break;
        } 
        ret += (next_st - st) * len;
        st = next_st;
        len++;
    }
    return ret;
}

void solve(int test_case) {
    int k; 
    cin >> k;
    
    int l = 1, r = 2e16; 
    int ans = 0;
    
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (calc(mid) <= k) { 
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    int sum = sumDigitsFrom1ToN(ans);
    int rem = k - calc(ans);
    if (rem > 0) {
        string x = to_string(ans + 1);
        for (int i = 0; i < rem; i++) {
            sum += x[i] - '0';
        }
    }
    
    cout << sum << ln;
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