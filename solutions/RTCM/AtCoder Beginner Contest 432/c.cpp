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


// ternary search on integers
int calc(int x){
    return 2*x; // your calculations here
}
int ternary_search(int l, int r) {
    while (r - l > 2) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        if (calc(m1) < calc(m2))  // > for min
            l = m1;
        else
            r = m2;
    }
    
    int best_x = l;
    for (int x = l; x <= r; x++) {
        if (calc(x) < calc(best_x)) best_x = x;
    }
    
    return best_x;  // Return the integer x that minimizes f(x)
}
void solve(int test_case) {
    int n,x,y; cin>>n>>x>>y;
    vi v(n); cin>>v;
    int dif = y-x;
    pair<int,int> rng = {0 , v[0]};
    for(int i = 1 ; i < n ;i++){
        int cur = x * (v[0] - v[i]);
        if(cur%dif){
            NA; return;
        }
        cur /= dif;
      //  cout<<cur<<ln;
        rng.first = max(rng.first,-cur);
        rng.second = min(rng.second , v[i] - cur);
       // cout<<rng.first<<' '<<rng.second<<ln;
    }
    if(rng.first > rng.second) NA;
    else{
        int sum1 = rng.second;
        int sum2 = rng.first;
        for(int i = 1 ; i < n; i++){
            int cur1 = (x * (v[0] - v[i])) / dif;
            sum1 += rng.second + cur1;
            int cur2 = (x * (v[0] - v[i])) / dif;
            sum2 += rng.first + cur2;
        }
        cout<<max(sum1,sum2)<<ln;
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