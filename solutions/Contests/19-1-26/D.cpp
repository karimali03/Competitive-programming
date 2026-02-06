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
       int n; cin>>n;
       vi v(n); cin>>v;
       vi nxt(n);
       vi deg(n);
       for(int i = 0;i < n ;i++){
            v[i]--;
            nxt[i] = v[i];
            deg[v[i]]++;
        }   
        vi vis(n);
        vi clr(n);
        queue<int>q;
        f(i,0,n) if(deg[i] == 0)  q.push(i); 
        while(!q.empty()){
            auto x = q.front(); q.pop();
            vis[x] = 1;
            if(clr[x] == 0){
                clr[x] = 2;
                clr[nxt[x]] = 1;
            }
            if(--deg[nxt[x]] == 0){
               q.push(nxt[x]);
            }
        }
        bool vld = true;
        vi path;
        function<void(int)> dfs = [&](int x){
            vis[x] = 1;
            path.push_back(x);
            if(!vis[nxt[x]])  dfs(nxt[x]);
        };

        f(i,0,n) if(!vis[i]){
            path.clear();
            dfs(i);
            int sz = path.size();
            int cb = 0;
            for(int i = 0;i < sz ; i++) if(clr[path[i]] == 1) cb++;
            if(cb == 0){
                if(sz&1) vld = false;
                int sw = 2;
                for(int i = 0;i < sz ; i++){
                    clr[path[i]] = sw;
                    sw = 3-sw;
                }
            }else{
                for(int i = 0;i < sz ; i++){
                    if(clr[path[i]] == 1){
                        int j = (i+1)%sz;
                        int sw = 2;
                        while(clr[path[j]] != 1){
                            clr[path[j]] = sw;
                            sw = 3 - sw;
                            j = (j+1)%sz;
                        }
                    }
                }
            }
           
        }
        if(!vld){
            NA;
            return;
        } 

        int cnt = 0;
        for(int i =0 ;i < n; i++) if(clr[i] == 2) cnt++;
        cout<<cnt<<ln;
        for(int i =0 ;i < n; i++) if(clr[i] == 2) cout<<v[i]+1<<" ";
        cout<<ln;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;

    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}