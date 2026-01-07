#include "bits/stdc++.h"
using namespace std;
#define vi vector<int>
#define ln "\n"
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define int long long



struct RollbackBIT {
    int n;
    vector<int> tree;
    vector<pair<int, int>> history; // Stores {index, value_added}

    RollbackBIT(int sz) : n(sz), tree(sz + 1, 0) {}

    // Add val to index idx
    void add(int idx, int val) {
        history.push_back({idx, val}); // Record for rollback
        for (; idx <= n; idx += idx & -idx) 
            tree[idx] += val;
    }

    // Prefix sum up to idx
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) 
            sum += tree[idx];
        return sum;
    }

    // Get range sum [l, r]
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }

    // --- Rollback Features ---

    // Get current state ID
    int snapshot() {
        return history.size();
    }

    // Revert to a previous state ID
    void rollback(int snap) {
        while ((int)history.size() > snap) {
            auto [idx, val] = history.back();
            history.pop_back();
            // Manually subtract to undo (don't call add() here)
            for (; idx <= n; idx += idx & -idx) 
                tree[idx] -= val;
        }
    }
};

void solve(){
    int n,b,r,w; cin>>n>>b>>r>>w;
    vi d(b);
    for(int i=0;i<b;i++){
        cin>>d[i];
        if(i) d[i] += d[i-1];
    } 
    vi v(n);
    for(int i=0;i<n;i++){
        cin>>v[i]; v[i]--;
    }
    RollbackBIT st2(b+10);
    auto can = [&](int time) -> bool{
        st2.rollback(0);
        int cost = 2  * w;
        ordered_set st; 
        st.insert(v[0]);
        st2.add(v[0]+1,1);
        int cnt = 1;
        int mx = 2*w + d[v[0]];
        int cur = v[0];
        for(int i = 1 ; i < n ; i++){
            int x = st.order_of_key(v[i]);
            int add = 2 * x * w + 2 * w;
            if(st.find(v[i]) == st.end()){
                int frq = st2.query(v[i]+2,b+4);
                add += frq * 2 * w;
            }
            int nc = cost + add + d[max(cur,v[i])];
            if(nc <= time){
                st.insert(v[i]);
                st2.add(v[i]+1,1);
                cost += add;
                cur = max(cur , v[i]);
                mx = max(mx , nc);
            }else{
                st.clear(); 
                st2.rollback(0);
                cost = cnt * r + 2 * w;
                st.insert(v[i]);
                cur = v[i];
                st2.add(v[i]+1,1);
                mx = max(mx , cost + d[v[i]]);
                cnt++;
            }
        }
        return mx <= time;
    };
    int lx = 1 , rx = 1e16;
    int ans = rx;
    while(lx<=rx){
        int mid = lx + (rx-lx)/2;
        if(can(mid)) ans=mid,rx = mid-1;
        else lx = mid+1;
    }
    cout<<ans<<ln;

}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    while(t--) solve();
    return 0;
}