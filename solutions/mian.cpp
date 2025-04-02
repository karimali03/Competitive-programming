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

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

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

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
 
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}


int SQ,sum;
int frq[1'000'001]{};
struct Query
{
    int l, r, idx;
    bool operator < (const Query &other) const
    {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;
        return (l/SQ) & 1 ? r > other.r : r < other.r;
    }
};
 
void add(ll val) {
    sum -= val * (frq[val]*frq[val]);
    frq[val]++;
    sum += val * (frq[val]*frq[val]);
}

void del(ll val) {
    sum -= val * (frq[val]*frq[val]);
    frq[val]--;   
    sum += val * (frq[val]*frq[val]);
}

vi MO(vector<Query> &q, vi &v){
    int n = v.size();
    SQ = sqrt(n) + 1;
    sum = 0;
    vi res(q.size());
    sort(q.begin(), q.end());
    int l = 0 ,r = -1;
    for(auto [lq,rq,idx] : q){
        while(lq < l) add(v[--l]);
        while(rq > r) add(v[++r]);
        while(lq > l) del(v[l++]);
        while(rq < r) del(v[r--]);
        res[idx] = sum;
    }
    return res;
}
void solve(int test_case){
    int n; cin>>n;
    int q; cin>>q;
    vi v(n); cin>>v;
    vector<Query> queries(q);
    for(int i = 0 ; i < q ; i++){
        int l,r; cin>>l>>r; l--,r--;
        queries[i] = {l,r,i};
    }
    vi ans = MO(queries,v);
    for(auto x : ans) cout << x << ln;
}