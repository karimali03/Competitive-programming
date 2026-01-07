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

int dist(pair<int,int>p){
    return p.first*p.first+p.second*p.second;
}

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vector<pair<int,int>>v(n); 
    int cnt = 0;
    for(int i  = 0 ; i < n ; i++){
        cin>>v[i].first>>v[i].second;
        if(v[i].first==v[i].second) cnt++;
    }
    vector<pair<int,int>>p;
    for(int i = 0 ; i < n ; i++) if(v[i].first != v[i].second) p.push_back(v[i]);
    vector<pair<int,int>>op;
    sort(all(p),[](pair<int,int>&a,pair<int,int>&b){
        if(a.first == b.first) return a > b;
        return a < b;
    });
    if(!p.empty()) op.push_back(p.back());
        sort(all(p),[](pair<int,int>&a,pair<int,int>&b){
        if(a.second == b.second) return a < b;
        return a.second < b.second;
    });
    if(!p.empty()) op.push_back(p.back());
        sort(all(p),[](pair<int,int>&a,pair<int,int>&b){
        if(a.first == b.first) return a > b;
        return a < b;
    });
    if(!p.empty()) op.push_back(p.back());
        sort(all(p),[](pair<int,int>&a,pair<int,int>&b){
        if(a.second == b.second) return a < b;
        return a.second < b.second;
    });
    if(!p.empty()) op.push_back(p.back());


    while(q--){
        int x,y; cin>>x>>y;
        if(cnt == n){
            NA; continue;
        }
    }
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