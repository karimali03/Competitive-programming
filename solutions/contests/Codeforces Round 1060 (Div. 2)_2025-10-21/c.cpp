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
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"
#define int ll
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

//  get divisors from 1 to N (Nlog(N))
const int N = 2'000'05;
vi divisors[N];
int cnt[N][2]{};
pair<ll,ll> cost[N][3];
void init(){
    for(int i = 1 ; i < N ; i++ ){
            for(int j = i; j < N ; j+=i){
                divisors[j].push_back(i);
            }
    }   
    for(int i = 0 ; i < N ; i++){
        cost[i][0] = cost[i][1]  = {1e16,1e16};
    }
}


void change(int a,int b,ll val){
    if(val < cost[a][b].first){
        cost[a][b].second = cost[a][b].first;
        cost[a][b].first = val;
    }else if(val < cost[a][b].second){
        cost[a][b].second = val;
    }
}
void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vector<ll> b(n); cin>>b;
    ll res = 1e16;
    int mx = *max_element(all(v))*2;
    for(int i = 0;i < n ; i++){
        for(auto it : divisors[v[i]]){
            if(it == 1) continue;
            cnt[it][0]++;
            change(it,0,0);
            if(cnt[it][0] == 2) res = 0;
            if(cnt[it][1]) res = min(res,cost[it][1].first);
        }
        for(auto it : divisors[v[i]+1]){
            if(it == 1) continue;
            cnt[it][1]++;
            change(it,1,b[i]);
            if(cnt[it][0]) res = min(res,cost[it][1].first);
            if(cnt[it][1] >= 2)
            res = min(res,cost[it][1].first+cost[it][1].second);
        }
    }
    for(int i = 0;i < n ; i++){
        for(auto it : divisors[v[i]]){
            if(it == 1) continue;
            cost[it][0] = {1e16,1e16};
            cnt[it][0]--;
        }
        for(auto it : divisors[v[i]+1]){
            if(it == 1) continue;
            cost[it][1] = {1e16,1e16};
            cnt[it][1]--;

        }
    }
    set<int>st;
    for(int i = 0;i < n ; i++){
        if(i && !st.empty()){
            auto it = st.lower_bound(v[i]);
            res = min(res , (*it-v[i])*b[i]);
        }
        if(v[i] != 1){
            for(int x = 1 ; x*v[i] <= mx ; x++){
                st.insert(x*v[i]);
            }
        }
    }
    st.clear();
    for(int i = n-1 ; i >= 0 ; i--){
        if(i != n-1 && !st.empty()){
            auto it = st.lower_bound(v[i]);
            res = min(res , (*it-v[i])*b[i]);
        }
        if(v[i] != 1){
            for(int x = 1 ; x*v[i] <= mx ; x++){
                st.insert(x*v[i]);
            }   
        }
    }
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}