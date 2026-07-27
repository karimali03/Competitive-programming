#include <bits/stdc++.h>
using namespace std;
#define ln "\n";
#define int long long
#define rall(X) X.rbegin(),X.rend()

int msb(int x){
    for(int i = 33 ; i >= 0 ; i--){
        if((x>>i)&1) return i;
    }
    return -1;
}
void solve(){
    int a,b,c;
    cin>>a>>b>>c;
    int aa=__popcount(a);
    int bb=__popcount(b);
    int cc=__popcount(c);
    int ma = msb(a);
    int mb = msb(b);
    int mc = msb(c);
    vector<array<int,4>> ch;
    ch.push_back({ma,aa,a,1});
    ch.push_back({mb,bb,b,2});
    ch.push_back({mc,cc,c,3});
    sort( rall(ch) );
    int idx = ch[0][3];
    if(idx==1)cout<<"Abady\n";
    else if(idx==2)cout<<"Taher\n";
    else cout<<"David\n";
}


signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
   cin>>t;
    while(t--) solve();
}