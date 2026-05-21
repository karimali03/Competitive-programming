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
const int N = 16;
int state[N][N];
int rec(int x,int y){
    if(x<0||x>15||y<0||y>15) return 1;
    int &ret = state[x][y];
    if(~ret) return ret;
    bool win = false;
    win |=( rec(x-2,y+1) == 0);
    win |=( rec(x-2,y-1) == 0);
    win |=( rec(x+1,y-2) == 0);
    win |=( rec(x-1,y-2) == 0);
    return ret = win;
}
void solve(int test_case) {
    int x,y; cin>>x>>y; x--,y--;
    memset(state,-1,sizeof state);
    if(rec(x,y)) cout<<"First\n";
    else cout<<"Second\n";
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