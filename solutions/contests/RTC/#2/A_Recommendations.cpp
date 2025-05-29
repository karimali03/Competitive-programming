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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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

struct SegmentTree {
    struct node {
        int val;
    };

    int n;
    int ty;
    vector<node> tree;
    node neutral = {0};  // Change for different operations

    SegmentTree(int size , int ty = 0): ty(ty) {
        n = 1;
        while (n < size) n <<= 1;
        if(ty) neutral = {INT32_MIN};
        else neutral = {INT32_MAX};
        tree.resize(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        return ( ty ? node{max(a.val,b.val)} : node{min(a.val,b.val)});
    }

    // Build the segment tree from a given array
    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    // Query in range [l, r]
    int query1(int v, int tl, int tr, int l, int r, int lf, int rh) {
    //  debug(l); debug(r); debug(tl); debug(tr); debug(tree[v].val);
        if (l > r || tree[v].val > lf) return INT32_MAX; // default value for min query
        if (l > tr || r < tl) return INT32_MAX; // out of segment
        if (l == tl && r == tr && (tr-tl) == 0)  return tl;
        int tm = (tl + tr) / 2;
        int x1 = query1(v * 2 + 1, tl, tm, l, min(r, tm),lf,rh);
        if(x1 != INT32_MAX) return x1;
        int x2 = query1(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r,lf,rh);
        return x2;
    }

    int query2(int v, int tl, int tr, int l, int r, int rh, int lf) {
    //    debug(l); debug(r); debug(tl); debug(tr); debug(tree[v].val);
        if (l > r || tree[v].val < rh) return -1; // default value for max query
        if (l > tr || r < tl) return -1; // out of segment
        if (l == tl && r == tr && (tr-tl) == 0)  return tl;
       
        int tm = (tl + tr) / 2;
        int x1 = query2(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r,rh,lf);
     //   debug(x1);
        if(x1 != -1) return x1;
        int x2 = query2(v * 2 + 1, tl, tm, l, min(r, tm),rh,lf);
     //   debug(x2);
        return x2;
    }
};

struct compress {
    vector<int> org;
    map<int,int>mp;
    int sz;
    compress(vector<int> v){
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        f(i,0,v.size()) mp[v[i]] = i;
        for(auto [a,b] : mp) org.push_back(a);
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
    int n; cin>>n;
    vi v;
    vii x(n,vi(2));
    map<pair<int,int>,int>cnt;
    f(i,0,n){
        cin>>x[i][0]>>x[i][1];
        v.push_back(x[i][0]);
        v.push_back(x[i][1]);
        cnt[{x[i][0],x[i][1]}]++;
    }
    compress com(v);
    vi st(com.sz,INT32_MIN) , en(com.sz,INT32_MAX);
    for(int i = 0 ; i < n ; i++){
        st[com.idx(x[i][0])] = max(st[com.idx(x[i][0])] ,com.idx(x[i][1]) );
        en[com.idx(x[i][1])] = min(en[com.idx(x[i][1])] ,com.idx(x[i][0]) );
    }
    SegmentTree ss(com.sz,1),ee(com.sz,0);
    ss.build(st,0,0,com.sz-1);
    ee.build(en,0,0,com.sz-1);
    vi res(n);
    for(int i = 0 ; i  < n ; i ++){
        int lf = com.idx(x[i][0]);
        int rh = com.idx(x[i][1]);
        if(cnt[{com.val(lf),com.val(rh)}] > 1) continue;
        int ans1 = ss.query2(0,0,com.sz-1,0,lf-1,rh,lf);
        if(ans1 == -1) ans1 = lf;
        int ans2 = ee.query1(0,0,com.sz-1,rh+1,com.sz-1,lf,rh);
        if(ans2 == INT32_MAX) ans2 = rh;
        if(st[lf] > rh) ans1 = lf;
        if(en[rh] < lf) ans2 = rh;
        lf = com.val(lf); rh = com.val(rh);
        ans1 = com.val(ans1); ans2 = com.val(ans2);
      //  debug(lf); debug(rh);
       // debug(ans1); debug(ans2);
        res[i] = (ans2-ans1+1)-(rh-lf+1);

    }
    for(auto it : res) cout<<it<<ln;

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