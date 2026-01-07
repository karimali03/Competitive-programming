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


// Structure to store city coordinates
struct Point {
    int x, y;
};

// Function to calculate Euclidean distance
double get_dist(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void solve(int test_case) {
    int n; cin>>n;
    vector<Point> v(n);
    for(int i = 0;i < n ; i++){
        cin>>v[i].x>>v[i].y;
    }
    vector<double> mn(n,1e18);
    vi vis(n);
    mn[0] = 0;
    double res = 0;
    for(int i = 0;i < n; i++){
        int cur = -1;
        for(int x = 0; x < n ; x++){
            if(!vis[x] && ( cur == -1 || mn[x] < mn[cur]) ) cur = x;
        }
        res += mn[cur];
        for(int x = 0; x < n ; x++){
            if(vis[x]) continue;
            mn[x] = min(mn[x] , get_dist(v[cur],v[x]));
        }
        vis[cur] = 1;
    }

    cout<<fixed<<setprecision(10)<<res<<ln;

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