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


struct Problem {
    int tm, score, idx;
};

struct State {
    bool ok = false;
    int score = 0;
    int penalty = 0;
    vi seq;
};

bool better(const State &a, const State &b) {
    if(!a.ok) return false;
    if(!b.ok) return true;
    if(a.score != b.score) return a.score > b.score;
    if(a.penalty != b.penalty) return a.penalty < b.penalty;
    return lexicographical_compare(all(a.seq), all(b.seq));
}

void solve() {
    int n,h; cin>>n>>h;
    vector<Problem> p(n);
    for(int i = 0;i < n ; i++){
        cin>>p[i].tm;
        p[i].tm /= 50;
        p[i].idx = i + 1;
    }
    for(int i = 0;i < n ; i++) cin>>p[i].score;

    sort(all(p), [](const Problem &a, const Problem &b) {
        if(a.tm != b.tm) return a.tm < b.tm;
        return a.idx < b.idx;
    });

    int total_time = h * 60;
    vector<State> dp(total_time + 1);
    dp[0].ok = true;

    for(const auto &prob : p){
        for(int tm = total_time; tm >= prob.tm; tm--){
            if(!dp[tm - prob.tm].ok) continue;
            State cur = dp[tm - prob.tm];
            cur.score += prob.score;
            cur.penalty += tm;
            cur.seq.push_back(prob.idx);
            if(better(cur, dp[tm])) dp[tm] = cur;
        }
    }

    State ans;
    for(int tm = 0; tm <= total_time; tm++){
        if(better(dp[tm], ans)) ans = dp[tm];
    }

    cout<<ans.seq<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++) {
        solve();
    }

    return 0;
}
