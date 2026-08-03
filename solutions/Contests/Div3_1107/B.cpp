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
#define int ll
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


bool vld(int num){
    vi vis(10);
    while(num){
        vis[num%10] = true;
        num/=10;
    }
    return count(all(vis),true) <= 2;
}

void solve(int test_case) {
    int i; cin>>i;
    cout<<100000001<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    // for(int i = 1 ; i <= 100000000 ; i++){
    //     if(vld(i)){
    //         int n = stoll(num);
    //         if(!vld(i*n)){
    //             cout<<n<<" "<<n*i<<ln;
    //         }
    //     }
    // }
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}