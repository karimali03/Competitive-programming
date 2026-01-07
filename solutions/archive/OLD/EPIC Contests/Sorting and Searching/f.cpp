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


// pivot is the index where is in correct place if the array is sorted
//  prev <= pivot < next
int make_pivot(vector<int>& v, int l, int r) {
    // choose random pivot using chrono
    int rand_idx = l + rand() % (r - l + 1);
    swap(v[rand_idx], v[r]);
    
    int idx = r;
    int cnt = 0;
    for (int i = l; i <= r; i++) 
    if (v[i] <= v[idx] && i != idx) cnt++;
    
    swap(v[idx], v[l + cnt]);
    idx = l + cnt;
    
    int x = l, y = r;
    while (x < idx && y > idx) {
        while (x < idx && v[x] <= v[idx]) x++;
        while (v[y] > v[idx]) y--;
        if (x < idx && y > idx) swap(v[x], v[y]); 
    }
    return idx;
}

void quick_sort(vector<int>& v, int l, int r) {
    if (l >= r) return;
    int pivot_idx = make_pivot(v, l, r);
    quick_sort(v, l, pivot_idx - 1);
    quick_sort(v, pivot_idx + 1, r);
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
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    int t = 1;
 
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}