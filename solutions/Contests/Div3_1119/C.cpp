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
    pair<int,int>rng = {-1,-1};
    int len = -1;
    vi lst(3,-1);
    if(v[0] == 1) lst[1]++;
    else if(v[0] == -1) lst[2] = 0;
    else lst[0]++;
    for(int i = 1 ;i  < n ; i++){
        if(v[i] != 0){
            if(lst[1] != -1){
                int c = i-lst[1]+1;
                if(len < c){
                    len = c;
                    rng = {lst[1] , i};
                }
            }
            else if(lst[2] != -1){
                int c = i-lst[2]+1;
                if(len < c){
                    len = c;
                    rng = {lst[2],i};
                }
            }
            if(v[i] == 1) lst[1] = i;
            else if(lst[2] == -1) lst[2] = i;
        }
    }

    if(len == -1){
        for(int i = 0;i < n ; i++) cout<<abs(v[i])<<" ";
        cout<<ln;
    }
    else{
        for(int i = 0;i < rng.first ; i++) cout<<abs(v[i])<<" ";
        cout<<"1 ";
        for(int i = rng.first+1 ; i < rng.second ; i++) cout<<"0 ";
        cout<<"1 ";
        for(int i = rng.second+1 ; i < n ; i++) cout<<abs(v[i])<<" ";
        cout<<ln;
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