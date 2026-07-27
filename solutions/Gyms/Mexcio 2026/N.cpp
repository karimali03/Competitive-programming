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

const int N = 105;
const int M = 305;
struct state{
    int score = 0,pen = 0;
    vi idx;
    bool operator<(const state &rhs) const {
        if(score != rhs.score) return score < rhs.score;
        if(pen != rhs.pen) return pen > rhs.pen;
        return lexicographical_compare(
            rhs.idx.rbegin(), rhs.idx.rend(),
            idx.rbegin(), idx.rend()
        );
    };
};
state dp[N][M];
int vis[N][M];
int tr = 0;
void solve(int test_case) {
    tr++;
    int n,h; cin>>n>>h;
    h *= 60;
    for(int i = 0;i < n ; i++){
        for(int j = 0;j <= h ; j++) dp[i][j].score = -1;
    }
    vector<array<int,3>> v(n);
    for(int i = 0;i < n; i++){
        cin>>v[i][0];
        v[i][0] /= 50;
        v[i][1] = i;
    }
    for(int i = 0;i < n ; i++){
        cin>>v[i][2];
    }
    sort(all(v));
    function<state(int,int)> rec = [&](int x,int y) -> state{
        if(x == n) return state();
        if(vis[x][y] == tr) return dp[x][y]; 
        vis[x][y] = tr;
        auto &ret = dp[x][y];
        ret = rec(x+1,y);
        if(v[x][0] + y <= h){
            state st = rec(x+1,y+v[x][0]);
            st.score += v[x][2];
            st.pen += (y + v[x][0]);
            st.idx.push_back(v[x][1]+1);
            ret = max(ret , st);
        }
        return ret;
    };
    auto res = rec(0,0);
    reverse(all(res.idx));
    cout<<res.idx<<ln;
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