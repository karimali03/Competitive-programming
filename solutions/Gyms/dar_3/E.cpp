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
    vector<pair<int,int>>v(n);
    f(i,0,n){
        cin>>v[i].first>>v[i].second;
    } 
    sort(all(v));
    vi slp;
    for(int i = 1 ; i < n ; i++){
        int dx = v[i].first - v[i-1].first;
        int dy = v[i].second - v[i-1].second;
        if(dx == 0 || dy == 0){
            cout<<"Not Mountains and Valleys\n";
            return;
        }
        if(v[i].second > v[i-1].second) slp.push_back(1);
        else slp.push_back(0);
    }
    bool vld = slp[0] == 1 && slp.back() == 0;
    for(int i = 1 ; i < (int)slp.size() ; i++){
        if(slp[i] == slp[i-1]) vld = false;
    }
    if(vld){
        cout<<"Mountains and Valleys\n";
    }else{
        cout<<"Not Mountains and Valleys\n";
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