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
   set<int>st = {1,2,4,7,8,11,13,14};
//    for(int i = 0;i < (1<<6); i++){
//         int cur = 0;
//         for(int j = 0;j < 6 ; j++){
//             if((i>>j)&1) cur ^= (3 * j);
//         }
//         st.insert(cur);
//    }
//    for(auto &it : st) cout<<it<<" ";
//    cout<<ln;
//    vector<set<int>>v(16);
//    for(int i = 0 ; i <= 15 ; i++){   
//        for(int j = 0 ; j <= 15 ; j += 3){
//             if(st.count(i^j)) v[i].insert(i^j); 
//        }
//    }
//    for(int i = 0;i < 16 ; i++){
//         cout<<i<<" : ";
//         for(auto &it : v[i]) cout<<it<<" ";
//         cout<<ln;
//    }
    int n,q; cin>>n>>q;
    int cnt =0 ;
    vi v(n); cin>>v;
    for(auto &it : v) if(st.count(it)) cnt++;
    cout<<n-cnt<<" ";
    while(q--){
        int a,b; cin>>a>>b; a--;
        if(st.count(v[a])) cnt--;
        v[a] = b;
        if(st.count(v[a])) cnt++;
        cout<<n-cnt<<" ";
    }
    cout<<ln;
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