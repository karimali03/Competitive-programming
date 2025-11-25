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


const int N = 1000005;
pair<int,int> idx[N];
bool exist[N];

void solve(int test_case) {
    f(i,0,N) idx[i] = {-1,-1};
    int n; cin>>n;
    vi v(n); cin>>v;
    pair<int,int> rng = {v[0] , v[n-1]};
    for(int i = 0 ; i < n ; i++){
        exist[v[i]] = 1;
        if(i) idx[v[i]].first = v[i-1];
        if(i != n-1) idx[v[i]].second = v[i+1];
    }
    int q; cin>>q;
    int sz = n;
    while(q--){
        char op; cin>>op;
        if(op == '?'){
            int x; cin>>x;
            vi cur(2*x); 
            int mx  = 0;
            int cnt = 0;
            for(int i = 0;i < 2*x ; i++){
                if(i < x) cin>>cur[i];
                else cur[i] = cur[i-x];
                if(exist[cur[i]]) mx = 1;
            }
            for(int i = 0;i < 2*x-1; i++){
                if(!exist[cur[i]]){
                    cnt = 0; continue;
                }
                if(cnt+1 == x) cnt = max(0ll , cnt-1);
                int nxt = idx[cur[i]].second;
                if(cur[i] == rng.second) nxt = rng.first;
                if(nxt == cur[i+1]) cnt++;
                mx = max(mx , cnt + 1);
            }
            if(mx < x) cout<<mx<<ln;
            else if(mx == sz) cout<<"*"<<ln;
            else cout<<mx<<ln;
        }else if(op == '+'){
            int x,y; cin>>x>>y;
            idx[x].first = idx[y].first;
            idx[x].second = y;
            idx[y].first = x;
            if(idx[x].first == -1) rng.first = x;
            exist[x] = 1;
            sz++;
        }else{
            int x; cin>>x;
            int prv = idx[x].first;
            int nxt = idx[x].second;
            idx[prv].second = nxt;
            idx[nxt].first = prv;
            if(idx[prv].second == -1) rng.second = prv;
            if(idx[nxt].first == -1) rng.first = nxt;
            idx[x] = {-1,-1};
            sz--;
            exist[x] = 0;
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