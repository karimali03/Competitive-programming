#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll 
#define vi vector<ll>
#define vii vector<vi>

const int N = 2e5+10;
void solve(){
    int n,q; cin>>n>>q;
    vi v(n);
    for(int i = 0;i < n ; i++) cin>>v[i];
    vi res(n);
    res[n-1] = v[n-1];
    int cur = v[n-1];
    for(int i = n-2 ; i >= 0 ; i--){
        if(cur < 0) cur = v[i];
        else cur += v[i];
        res[i] = max(cur , res[i+1]);
    }
    while(q--){
        int x; cin>>x;
        cout<<res[x]<<"\n";
    }

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
