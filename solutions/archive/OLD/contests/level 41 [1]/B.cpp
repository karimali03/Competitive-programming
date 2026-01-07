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




struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_){
        n = n_;
        bit.assign(n+1, 0); // 1-indexed, supports indices 1..n
    }
    void add(int idx, int val){ // idx is 1..n
        while(idx <= n){
            bit[idx] = (bit[idx] + val);
            idx += idx & -idx;
        }
    }
    int sumPrefix(int idx){ // sum 1..idx
        int res = 0;
        while(idx > 0){
            res = (res + bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
    // sum on [l..r] with l,r in 1..n
    int sumRange(int l, int r){
        if(l > r) return 0;
        return (sumPrefix(r) - sumPrefix(l-1));
    }
};

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    Fenwick st(n);
    for(int i = 0;i < n ; i++) st.add(i+1,v[i]);
    set<int>l,r;
    for(int i = 0;i<n;i++) if(v[i] == 1){
        if(i) l.insert(i-1);
        if(i != n-1) r.insert(i+1);
    }
    while(q--){
        int op; cin>>op;
        if(op == 1){
            int x; cin>>x;
            bool vld = false;
            if(!l.empty() && st.sumRange(1,*l.rbegin()+2) >= x) vld = true;
            if(!r.empty() && st.sumRange(*r.begin(),n) >= x) vld = true;
            if(vld){
                YES; continue;
            }
            int l = 1 , r = n;
            while(l<=r){
                int mid = l + (r-l)/2;
                int sum = st.sumRange(1,mid);
                if(sum == x){
                    vld = true; break;
                }
                if(sum > x) r = mid-1;
                else l = mid+1;
            }
            l = n , r = 1;
            while(l<=r){
                int mid = l + (r-l)/2;
                int sum = st.sumRange(mid,n);
                if(sum == x){
                    vld = true; break;
                }
                if(sum > x) r = mid+1;
                else l = mid-1;
            }
            if(vld) YES;
            else NO;
        }else{
            int x,y; cin>>x>>y; x--;
            if(v[x] == 1){
                if(x) l.erase(x-1);
                if(x != n-1) r.erase(x+1); 
            }
            st.add(x+1,y-v[x]);
            v[x] = y;
            if(v[x] == 1){
                if(x) l.insert(x-1);
                if(x != n-1) r.insert(x+1); 
            }
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