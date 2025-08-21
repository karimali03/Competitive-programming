#include "bits/stdc++.h"
#define ll long long
#define vi vector<ll>
#define all(X) X.begin(), X.end()

using namespace std;


int todec(string &s){
    int ret = 0;
    int n = s.size();
    int cnt = 1;
    for(int i = n-1 ; i>= 0 ; i--){
        if(s[i] == '1') ret+=cnt;
        cnt*=2;
    }
    return ret;
}
void solve() {
    string s; cin>>s;
    int n = s.size();
    map<int,pair<int,int>>mp;
    for(int i = 1 ; i <= 32 ; i++){
        for(int j = 0  ;  j+i <= n  ; j++){
            string x = s.substr(j,i);
            int ret = todec(x);
            if(!mp.count(ret)) mp[ret] = {j,j+i-1};
            else{
                if(j < mp[ret].first) mp[ret] = {j,j+i-1};
                else if(j == mp[ret].first && (j+i-1) < mp[ret].second)
                mp[ret] = {j,j+i-1};
            }
        }
    }
    vi v; 
    for(auto [x,y] : mp) v.push_back(x);
    v.push_back(1e15);
    int q; cin>>q;
    while(q--){
        int l,r; cin>>l>>r;
        auto bs = lower_bound(all(v),l);
        if(*bs > r) cout<<"-1 -1\n";
        else cout<<mp[*bs].first+1<<" "<<mp[*bs].second+1<<"\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    
    int size;
    size = 1;
   // cin >> size;
    while (size--) solve();    
}