#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

void solve(int test_case){
    int n,r,m; cin>>n>>r>>m;
    vii adj(n);
    f(i,0,r){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y); adj[y].push_back(x);
    }
    vi val(n);
    vi vis(n);
    set<pair<int,int>>st;
    f(i,0,m){
        int a,b; cin>>a>>b; a--,b++;
        val[a] = b; vis[a] = 1;
        st.insert({b,a});
    }   
    while(!st.empty()){
        auto cur = *st.rbegin(); st.erase(*st.rbegin()); 
        vis[cur.second] = 1;
        val[cur.second] = max(val[cur.second],cur.first);
        if(val[cur.second] > 1){
            for(auto it : adj[cur.second]){
                if(!vis[it]){ 
                    if(val[cur.second] - 1 > val[it]){
                        if(st.count({val[it],it})) st.erase({val[it],it});
                        val[it] = val[cur.second]-1;
                        st.insert({val[it],it});
                    }
                }
            }
        }
    }
    int cnt =0 ;
    f(i,0,n) if(val[i]) cnt++;
    if(cnt == n) cout<<"Yes\n";
    else cout<<"No\n";

}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}