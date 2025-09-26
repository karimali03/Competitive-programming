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



void solve(int test_case) {
    int n; cin>>n;
    int mask = 0;
    for(int i = n ; i >= 0;  i--){
        int x; cin>>x;
        if(x) mask = mask | (1<<i);
    }
    queue<int>q; q.push(mask);
    vi dist(6e6,-1);
    dist[mask] = 0;
    while(!q.empty()){
        auto cur = q.front(); q.pop();
      //  cout<<bitset<22>(cur).to_string()<<" "<<dist[cur]<<ln;
        if(cur == 1){
            cout<<dist[1]<<ln;
            return;
        }
        if(cur&1){
            int term = cur ^ (cur<<1) ^ 1;
            if(dist[term] == -1){
                dist[term] = 1 + dist[cur]; q.push(term);
            }
        }else{
            int term = cur>>1;
            if(dist[term] == -1){
                dist[term] = 1 + dist[cur]; q.push(term);
            }
        }
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