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


struct dsu {
    vector<int> size, par;
    int cc;

    dsu(int n) : cc(n), size(n, 1), par(n) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        par[x] = y;
        size[y] += size[x];
        cc--;
        return true;
    }

    vii get_cmp(){
        int n = par.size();
        vii ret(n);
        for(int i = 0;i < n ; i++){
            ret[get(i)].push_back(i);
        }
        sort(all(ret),[](vi& x,vi &y){
            return x.size() > y.size();
        });
        while(ret.back().empty()) ret.pop_back();
        return ret;
    }

};

void solve(int test_case) {
    int n,m; cin>>n>>m;
    dsu st(n);
    for(int i = 0;i < m ; i++){
        int x,y; cin>>x>>y; 
        st.merge(x,y);
    }
    auto cmp = st.get_cmp();
    priority_queue<pair<int,int>>q;
    vector<pair<int,int>>ret;
    for(int i = 0 ;i < (int)cmp.size() ; i++){
        q.push({cmp[i].size() , i});    
    }
    while(q.size() > 1){
        auto a = q.top(); q.pop();
        auto b = q.top(); q.pop();
        ret.push_back({cmp[a.second].back(),cmp[b.second].back()});
        cmp[a.second].pop_back();
        cmp[b.second].pop_back();
        if(a.first != 1) q.push({a.first-1,a.second});
        if(b.first != 1) q.push({b.first-1,b.second});
    }
    cout<<ret.size()<<ln;
    for(auto [a,b] : ret){
        cout<<a<<" "<<b<<ln;
    }

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