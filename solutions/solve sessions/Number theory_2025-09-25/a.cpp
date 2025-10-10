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

/*
  a * x + b * y = gcd(a, b)
  The general solution can be written as:
  x = x₀ + (b / gcd(a, b)) * t
  y = y₀ - (a / gcd(a, b)) * t
  where t is any integer, and (x₀, y₀) is the particular solution.
*/
int EEA(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = EEA(abs(a), abs(b), x0, y0);
    if (c % g)    return false;
    
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution(int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

pair<int,int> find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return {-1,-1};
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b); 
    if (x < minx)
        shift_solution(x, y, a, b, sign_b); // fitst [x,y] where x >= minX
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);  // last [x,y] where x <= maxX
    int rx1 = x;
    
    shift_solution(x, y, a, b, -(miny - y) / a);  // fitst [x,y] where y >= minY
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return {-1,-1};
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);  // last [x,y] where y <= maxY
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2); // intersection bettwen two ranges
    int rx = min(rx1, rx2);
    if (lx > rx) return {-1,-1};
    return {lx,rx};
}



void solve(int test_case) {
    int n; 
    while(cin>>n && n){
        int n1,c1,n2,c2; cin>>c1>>n1>>c2>>n2;
        auto [l,r] = find_all_solutions(n1,n2,n,0,n,0,n);
        if(l == -1){
            cout<<"failed\n"; continue;
        }
        int ch1 = l * c1 + ((n-l*n1)/n2) * c2;
        int ch2 = r * c1 + ((n-r*n1)/n2) * c2;
        if(ch1 < ch2) cout<<l<<" "<<((n-l*n1)/n2)<<ln;
        else cout<<r<<" "<<((n-r*n1)/n2)<<ln;
    }
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