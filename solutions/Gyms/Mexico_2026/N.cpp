#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll 
#define vi vector<ll>
#define vii vector<vi>

const int N = 2e5+10;
void solve(){
    int l,r; cin>>l>>r;
    int cnt = 0;
    for(int i = 1 ; i  <= r ; i++){
        int cur = i * (i+1) / 2;
        if(cur  > r) break;
        if(cur >= l) cnt++;
    }
    cout<<cnt<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
