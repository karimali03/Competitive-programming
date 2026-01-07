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

// Better random number generator
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void quick_sort(vector<int>& v, int l, int r) {
    if (l >= r) return;

    // 1. Choose Random Pivot
    int rand_idx = l + rng() % (r - l + 1);
    swap(v[l], v[rand_idx]);
    int pivot = v[l];

    // 2. 3-Way Partitioning
    int lt = l;      // Boundaries for "Less Than"
    int gt = r;      // Boundaries for "Greater Than"
    int i = l + 1;   // Current element scanner

    while (i <= gt) {
        if (v[i] < pivot) {
            swap(v[i], v[lt]);
            lt++;
            i++;
        } else if (v[i] > pivot) {
            swap(v[i], v[gt]);
            gt--;
        } else {
            i++;
        }
    }

    // lt is now the start of the "Equal" block
    // gt is now the end of the "Equal" block
    // We only recurse on the parts strictly less than or greater than
    quick_sort(v, l, lt - 1);
    quick_sort(v, gt + 1, r);
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    quick_sort(v,0,n-1);
    cout<<v<<ln;
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