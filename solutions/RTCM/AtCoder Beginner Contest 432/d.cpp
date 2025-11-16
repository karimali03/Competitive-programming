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
    int n,x,y; cin>>n>>x>>y;
    vector<array<int,4>>v;
    v.push_back({0,x-1,0,y-1});

    for(int i = 0;i < n ;i++){
        vector<array<int,4>> cur;
        char c; cin>>c;
        int a,b; cin>>a>>b;
        if(c == 'X'){
            for(auto it : v){
                pair<int,int> s1 = {it[0] , min(a-1,it[1])};
                pair<int,int> s2 = { max(a,it[0]), it[1]};
                if(s1.first <= s1.second) cur.push_back({s1.first,s1.second,it[2]-b,it[3]-b});
                if(s2.first <= s2.second) cur.push_back({s2.first,s2.second,it[2]+b,it[3]+b});
            }
        }else{
            for(auto it : v){
                pair<int,int> s1 = {it[2] , min(a-1,it[3])};
                pair<int,int> s2 = {max(a,it[2]), it[3]};
                if(s1.first <= s1.second) cur.push_back({it[0]-b,it[1]-b,s1.first,s1.second});
                if(s2.first <= s2.second) cur.push_back({it[0]+b,it[1]+b,s2.first,s2.second});
            } 
        }
        v = cur;
    }

    int sz = v.size();
    vi vis(sz);
    int cnt = 0;
    auto calc = [&](array<int,4> &arr)->int{
        return (arr[1]-arr[0]+1)*(arr[3]-arr[2]+1);
    };

    auto intersect = [&](array<int,4>&a,array<int,4>&b) -> bool{
        bool xi = (a[1] == b[0]-1)  || (b[1] == a[0]-1);
        if(max(a[2],b[2]) <= min(a[3],b[3]) && xi) return true;
        bool yi = (a[3] == b[2]-1) || (b[3] == a[2]-1);
        if(yi && max(a[0],b[0]) <= min(a[1],b[1])) return true;
        return false;
    };
    function<void(int)> dfs = [&](int i){
        vis[i] = 1;
        cnt += calc(v[i]);
        for(int j =0; j < sz ; j++) if(!vis[j]){
            if(intersect(v[i],v[j])) dfs(j);
        }
    };

    vi res;
    for(int i = 0; i< sz ; i++){
        if(!vis[i]){
            dfs(i);
            res.push_back(cnt); cnt=0;
        }
    }
    sort(all(res));
    cout<<res.size()<<ln;
    for(auto it:res) cout<<it<<" ";
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