#include "bits/stdc++.h"
#define ll long long
#define vi vector<ll>
#define int ll
#define all(v) v.begin(),v.end()
using namespace std;
#define YES cout<<"YES\n";
#define NO cout<<"NO\n";
void solve() {
    int n,k;
    cin>>n>>k;
    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    if(n == 0){
        return;
    }
    sort(all(v));
    if(k>=*max_element(all(v))){
        for(int i=n-1;i>=0;i--){
            cout<<v[i]<<" ";
        }
        return;
    }
    else if(k<=*min_element(all(v))){
        for(int i=0;i<n;i++){
            cout<<v[i]<<" ";
        }
        return;
    }
    else{
        int l = 0 ,r = n;
        int i =0;
        while (i < n && v[i] <= k)
        {
            if(v[i] == k) l--;
            l++,r--,i++;
        }
        // up
        int up = l * (v.back()-k);
        // down
        int down = r * (k-v[0]);
        if(up <= down){
            int cur = i;
            if(v[i-1] == k) cur--;
            for(int x = cur ; x < n ; x++) cout<<v[x]<<" ";
            for(int x = cur-1 ; x >= 0 ; x--) cout<<v[x]<<" ";
            cout<<"\n";
        }
        else{
            int cur = i-1;
            for(int x = cur ; x >= 0 ; x--) cout<<v[x]<<" ";
            for(int x = cur+1 ; x < n ; x++) cout<<v[x]<<" ";
            cout<<"\n";
        }
    }
}
signed main() {
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    
    return 0;
}