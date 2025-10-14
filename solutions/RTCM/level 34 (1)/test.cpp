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


// Function to safely calculate (a * b) % m without overflow.
// This is necessary when a, b, and m are close to the long long limit.
long long modular_multiply(long long a, long long b, long long m) {
    long long result = 0;
    a %= m;
    while (b > 0) {
        // If b is odd, add a to the result
        if (b % 2 == 1) {
            result = (result + a) % m;
        }
        // Double a and halve b
        a = (a * 2) % m;
        b /= 2;
    }
    return result;
}

// Function to find the Extended GCD of a and b
long long extendedGcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd = extendedGcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

// Function to solve a system of congruences using the Chinese Remainder Theorem.
// Returns {-1, -1} if no solution exists.
std::pair<long long, long long> crt(const std::vector<long long>& a, const std::vector<long long>& m) {
    if (a.empty() || m.empty()) {
        return {0, 1};
    }

    long long current_a = a[0];
    long long current_m = m[0];

    for (size_t i = 1; i < a.size(); ++i) {
        long long next_a = a[i];
        long long next_m = m[i];
        
        long long x, y;
        long long g = extendedGcd(current_m, next_m, x, y);

        long long diff = next_a - current_a;
        
        if (diff % g != 0) {
            return {-1, -1};
        }

        // WARNING: This is the line that can overflow if the LCM is too large.
        long long new_m = (current_m / g) * next_m;
        
        long long mod_for_k = next_m / g;
        long long k_part1 = (diff % next_m + next_m) % next_m / g;
        long long inv_x = (x % mod_for_k + mod_for_k) % mod_for_k;

        long long k = modular_multiply(k_part1, inv_x, mod_for_k);

        long long term_to_add = modular_multiply(k, current_m, new_m);
        current_a = (current_a + term_to_add) % new_m;
        
        current_m = new_m;
        current_a = (current_a + current_m) % current_m;
    }

    return {current_a, current_m};
}


void solve(int test_case) {
    vi a = {6,2,1};
    vi m = {8,7,5};
    auto res = crt(a,m);
    cout<<res.first<<" "<<res.second<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;

    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}