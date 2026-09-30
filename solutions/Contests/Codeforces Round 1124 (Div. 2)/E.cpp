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
vector<int> NGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,n);
    for(int i = 1 ; i < n ; i++){
        while(!st.empty() && v[st.top()] < v[i]){ // > for NSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> PGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,0);
    for(int i = n-1 ; i > 0 ; i--){
        while(!st.empty() && v[st.top()] <= v[i]){ // > for PSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

int vis[262145]{};
int lst[262145]{};
int c = 0;
void solve(int test_case) {
    int n; cin>>n;
    vi v(n+1); 
    for(int i = 1 ;i  <= n ; i++) cin>>v[i];
    auto pg = PGE(v);
    auto ng = NGE(v);
    auto can = [&](int msk) -> bool{
        vi b(n+1),sum(n+1);
        c++;
        for(int i = 1;i <= n ; i++){
            b[i] = v[i] & msk;
            sum[i] = b[i] ^ sum[i-1];
        }
        for(int i = 1;i <= n ; i++){
            int mx = v[i];
            int l = pg[i]+1 , r = ng[i]-1;
            bool vld = ((msk&mx) == msk);
            if(vld && vis[sum[i]^msk] == c && lst[sum[i]^msk] >= l-1){
                return true;
            }
            vis[sum[i-1]] = c; lst[sum[i-1]] = i-1;
            if(vld && r-i <= i-l){
                    for(int j = i+1 ; j <= r ; j++){
                        int tag = sum[j] ^ msk;
                        // l-1 -> i-1
                        if(vis[tag] == c && lst[tag] >= l-1){
                            return true;
                        }
                    }
            }
        }
        c++;
        for(int i = n ; i >= 1 ; i--){
            int mx = v[i];
            int l = pg[i]+1 , r = ng[i]-1;
            bool vld = (msk&mx) == msk;
            if(vld && vis[sum[i-1]^msk] == c && lst[sum[i-1]^msk] <= r){
                return true;
            }
            vis[sum[i]] = c; lst[sum[i]] = i;
            if(vld && r-i > i-l){
                    for(int j = l-1 ; j < i-1 ; j++){
                        int tag = sum[j] ^ msk;
                        // i -> r
                        if(vis[tag] == c && lst[tag] <= r){
                            return true;
                        }
                    }
            }
        }
        return false;
    };

    int ans = 0;
    for(int b = 17 ; b >= 0 ; b--){
        if(can(ans | (1 << b))){
            ans |= (1 << b);
        }
    }
    cout<<ans<<ln;
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