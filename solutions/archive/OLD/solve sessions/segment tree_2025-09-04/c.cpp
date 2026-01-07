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


struct FenwickTree{
    static const int N = 1e6+5;
    ll bit[N] {};

    ll merge(int a,int b){
        return a + b;
    }
    // 1 based , add val to idx
    void add(int idx,ll val){
        while( idx < N){
            bit[idx] = merge(bit[idx] , val);
            idx+=idx&-idx;
        }
    }
    // from 1 to idx
    ll query(int idx){
        ll ret=0;
        while(idx>0){
            ret = merge(ret , bit[idx]);
            idx-=idx&-idx;
        }
        return ret;
    }
    // from l to r inclusive 
    ll prefix(int l,int r){
        return query(r)-query(l-1);
    }
};


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
    vi vals;
    f(i,0,n) vals.push_back(v[i]);
    vector<array<int,3>>queries(q);
    for(int i = 0 ; i < q;i++){
        char ch; cin>>ch;
        int x,y; cin>>x>>y;
        if(ch == '!'){
            x--; vals.push_back(y);
            queries[i] = {1 , x , y};
        }else{
            queries[i] = {2 , x , y};
            vals.push_back(x); vals.push_back(y);
        }
    }

    compress cm(vals);
    FenwickTree st;
    for(int i = 0 ; i < n ; i++) st.add(cm.idx(v[i])+1,1);
    for(int i = 0 ;i  <q ; i++) {
        if(queries[i][0] == 1){
            int id = queries[i][1];
            int val = queries[i][2];
            st.add(cm.idx(v[id])+1,-1);
            v[id] = val;
            st.add(cm.idx(val)+1,1);
        }else{
            int l = queries[i][1];
            int r = queries[i][2];
            cout<<st.prefix(cm.idx(l)+1,cm.idx(r)+1)<<ln;
        }
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