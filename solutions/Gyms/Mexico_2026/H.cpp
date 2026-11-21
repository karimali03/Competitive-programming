    #include <bits/stdc++.h>
    using namespace std;
    #define ll long long
    #define int ll 
    #define vi vector<ll>
    #define vii vector<vi>

    const int N = 2e5+10;
    void solve(){
        int n; cin>>n;
        vi v(n); 
        int mn = 1e10; int mx = 0;
        for(int i = 0;i  < n ;i++){
            cin>>v[i];
            mn = min(mn , v[i]); mx = max(mx , v[i]);
        } 
        int res = mx - mn;
        cout<<res<<"\n";
    }

    signed main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t = 1;
        // cin >> t;
        while(t--) solve();
        return 0;
    }
