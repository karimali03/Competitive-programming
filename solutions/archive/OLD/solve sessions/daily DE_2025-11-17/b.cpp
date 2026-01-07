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

int clearMSBtoI(int num,int i){
    // 1234i5678
    // 000005678
    int mask = (1 << i) - 1;
    return num & mask;
}

int MSB(int x){
    ll msb = 0;
    while (x){
        x >>= 1;
        msb++;
    }
    return msb - 1;
}


void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    set<int>st;
    for(int i = max(0ll,n-50) ; i < n ; i++) st.insert(i);
    for(int bit = 30 ; bit >= 0 ; bit--){
        int mx = 0 , mxi = 0;
        int mx2 = 0,  mxi2 = 0;
        for(int i = 0; i < n ; i++){
            int val = clearMSBtoI(v[i],bit+1);
            if(val > mx) mx=val,mxi=i;
            else if(val > mx2) mx2=val,mxi2=i;
        }
        st.insert(mxi); st.insert(mxi2);
    }
    vi ind(all(st));
    vi base;
    int sz = ind.size();
    for(auto it : ind) base.push_back(v[it]);
    while(q--){
        int x; cin>>x;
        vi cur = base;
        int res = 0;
        for(int bit = 30 ; bit >= 0 ; bit--){
            if(!((x>>bit)&1)) continue;
            int mni = 0;
            int mn = 1e10;
            for(int i=0;i<sz;i++){
                if(cur[i] > (1<<bit)) mni = i,mn=0;
                else{
                    int cost = (1<<bit) - cur[i];
                    if(cost < mn) mn=cost,mni=i;
                }
            }
            res += mn;
            if(MSB(cur[mni]) == bit) cur[mni] = clearMSBtoI(cur[mni],bit);
            if((1<<bit) > cur[mni]) cur[mni] = 0;
            else cur[mni] = (1<<bit)-1;
        }
        cout<<res<<ln;
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