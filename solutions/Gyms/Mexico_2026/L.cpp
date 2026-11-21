#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll 
#define vi vector<ll>
#define vii vector<vi>


const int M = 1e9+9;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
const ll B = uniform_int_distribution<ll>(0,M-1)(rng);

const int N = 2e5+10;
void solve(){
    int n; cin>>n;
    vector<set<int>>st(51);
    int mx = 0;
    for(int i = 0;i < n ;i++){
        string s; cin>>s;
        int sz = s.size();
        int hs = 0;
        for(int j = 0;j < sz ; j++){
            hs = hs * B + B * (s[j]-'a'+1); 
            hs %= M;
            if(st[j+1].count(hs)) mx = max(mx , j+1);
            st[j+1].insert(hs);
        }
    }
    cout<<mx<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
