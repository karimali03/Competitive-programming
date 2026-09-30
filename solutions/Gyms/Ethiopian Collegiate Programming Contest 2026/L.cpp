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
    int n,q,c; cin>>n>>q>>c;
    vector<pair<int,int>>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i].first>>v[i].second;
    }
    sort(all(v));
    vector<pair<int,int>>query(q);
    for(int i=0;i<q;i++){
        cin>>query[i].first;
        query[i].second = i;
    }
    sort(all(query));
    int ptr=0;
    int tot = 0;
    vi cnt(361);
    vi res(q);
    for(int i = 0;i < q ; i++){
        auto [d,id] = query[i];
        while(ptr < n && v[ptr].first <= d){
            cnt[v[ptr].second]++; tot++;
            ptr++;
        }
        if(tot < c){
            res[id] = -1; continue;
        }
        int mn=360,sum=0,r=1;
        for(int l = 1; l <= 360 ; l++){
            while(r < l+360 && sum < c){
                int ang = (r-1)%360 + 1;
                sum += cnt[ang];
                r++;
            }
            if(sum >= c) mn = min(mn , r-l);
            sum -= cnt[l];
        }
        res[id] = mn;
    }
    for(auto &it : res) cout<<it<<ln;
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