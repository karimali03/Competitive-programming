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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
struct compress {
    vector<int> org;
    map<int,int>mp;
    int sz;
    compress(vector<int> v){
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        for(int i = 0 ;i < (int)v.size() ; i++) mp[v[i]] = i;
        for(auto &[a,b] : mp) org.push_back(a);
        sz = v.size();
    }
    int idx(int val){
        return mp[val];
    }

    int val(int idx){
        return org[idx];
    }
};
void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    compress cm(v);
    vii pos(cm.sz);
    vi vv(n);
    for(int i = 0;i<n;i++){
        vv[i] = cm.idx(v[i]);
        pos[vv[i]].push_back(i);
    } 
    while(q--){
        int l,r; cin>>l>>r; l--,r--;
        set<int>res;
        for(int i = 0 ; i < 100 ; i++){
            int rnd = l + rng()%(r-l+1);
            int frq = upper_bound(all(pos[vv[rnd]]),r) - lower_bound(all(pos[vv[rnd]]),l);
            if(frq > (r-l+1)/3) res.insert(v[rnd]);
        }
        if(res.empty()) cout<<-1<<ln;
        else {
            for(auto &it : res) cout<<it<<" ";
            cout<<ln;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}