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


#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>



struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_){
        n = n_ + 5;
        bit.assign(n+1, 0); // 1-indexed, supports indices 1..n
    }
    // idx is 1..n
    void add(int idx, ll val){ 
        idx++;
        while(idx <= n){
            bit[idx] = (bit[idx] + val);
            idx += idx & -idx;
        }
    }
    // sum 1..idx
    ll sumPrefix(int idx){ 
        idx++;
        ll res = 0;
        while(idx > 0){
            res = (res + bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
    // sum on [l..r] with l,r in 1..n
    ll sumRange(int l, int r){
        if(l > r) return 0;
        return (sumPrefix(r) - sumPrefix(l-1));
    }
    // for range update , point query
    // update [l,r] +x  -> add(l,x) , add(r+1,-x) 
    // get idx  -> sumPrefix(idx)
};

// find_by_order(k): returns an iterator to the kth element (counting from zero) in the set
// order_of_key : returns to the number of items that are strictly smaller than our item k
#define int ll

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    Fenwick in(n),out(n);
    ordered_set st;
    for(int i = 0;i < n ; i++){
        int x = (int)st.size() - st.order_of_key(v[i]+1);
        in.add(i,x);
        st.insert(v[i]);
    }
    st.clear();
    for(int i = n-1 ; i >= 0;  i--){
        int x = st.order_of_key(v[i]);
        out.add(i,x);
        st.insert(v[i]);
    }
    while(q--){
        int op,x; cin>>op>>x;
        if(op == 1){
            x--;
            // x , x+1
            int vx_in = in.sumRange(x,x);
            int vx_out = out.sumRange(x,x);
            int vx1_in = in.sumRange(x+1,x+1);
            int vx1_out = out.sumRange(x+1,x+1);
            in.add(x , vx1_in - vx_in); out.add(x , vx1_out - vx_out);
            in.add(x+1, vx_in - vx1_in); out.add(x+1 , vx_out - vx1_out);
            if(v[x] > v[x+1]){
                out.add(x+1,-1);
                in.add(x,-1);
            }else{
                out.add(x,1);
                in.add(x+1,1);
            }
            swap(v[x],v[x+1]);
        }else{
            x--;
            int in1 = in.sumRange(0,x);
            int out1 = out.sumRange(0,x);
        //    int in2 = in.sumRange(x+1,n-1);
            int out2 = out.sumRange(x+1,n-1);
            int res = out2 + in1 + (x+1) * (n - x - 1);
            int xx = max(0ll , out1 - in1);
            res -= xx;
          //  cout<<in1<<" "<<out1<<" "<<in2<<" "<<out2<<" "<<(x+1)*(n-x-1)<<" "<<xx<<ln;
            cout<<res<<ln;
        }  
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}