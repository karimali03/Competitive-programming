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
    vi v(n); cin>>v;
    vii frq(2005);
    for(int i=0;i<n;i++) frq[v[i]].push_back(i);
    map<int,pair<int,int>>X;
    for(int i = 1 ; i <= 2000 ; i++){
        if(frq[i].empty()) continue;
        if(frq[i].size() >= 4){
            YES;
            cout<<frq[i][0]+1<<" "<<frq[i][1]+1<<" "<<frq[i][2]+1<<" "<<frq[i][3]+1<<ln;
            return;
        }
        for(int j = i+1 ; j <= 2000 ; j++){
            if(frq[j].empty()) continue;
            if(frq[i].size() > 1 && frq[j].size() > 1){
                YES;
                cout<<frq[i][0]+1<<" "<<frq[j][0]+1<<" "<<frq[i][1]+1<<" "<<frq[j][1]+1<<ln;
                return;
            }
            int val = (i ^ j) * (i + j) + (i ^ j) * (i ^ j);
            if(X.count(val)){
                YES;
                cout<<frq[X[val].first][0]+1<<" "<<frq[X[val].second][0]+1<<" ";
                cout<<frq[i][0]+1<<" "<<frq[j][0]+1<<ln;
                return;
            }
            X[val] = {i,j};
        }
    }
    NO;
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