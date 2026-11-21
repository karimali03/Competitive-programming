#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vii vector<vi>

const int N = 2e5+10;
void solve(){
    int n; cin>>n;
    vi v(n); 
    vector<array<int,3>>st(n);
    for(int i = 0;i < n ; i++) cin>>v[i];
    for(int i = 0;i < n ; i++){
        st[i] = {v[i] , n-1-v[i] , i};
    }
    vii res(n,vi(n,-1));
    for(int i = 0;i < n ;i++){
        auto [x,y,z] = st[i];
        sort(st.begin()+i+1,st.begin()+n);
        // low win , need lose
        for(int j = i+1 ; j < n ; j++){
            auto [a,b,c] = st[j];
            if(x && b && res[z][c] == -1){
                x--; b--; res[z][c] = 1; res[c][z] = 0;
            } 
            st[j] = {a,b,c};
        }
        for(int j = i+1 ; j < n ; j++){
            auto [a,b,c] = st[j];
            if(y && a && res[z][c] == -1){
                y--; a--; res[c][z] = 1; res[z][c] = 0;
            } 
            st[j] = {a,b,c};
        }
        if(x || y){
            cout<<"NO\n"; return;
        }
    }

    cout<<"YES\n";
    for(int i=0;i<n;i++) res[i][i] = 0;
    for(int i = 0;i <  n; i++){
        for(int j = 0;j < n; j++){
            cout<<res[i][j];
        }
        cout<<"\n";
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
