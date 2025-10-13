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



void solve(int test_case) {
    int n; cin>>n;
    set<int>st; 
    f(i,0,n*n+1) st.insert(i);
    auto ask = [&]() -> vector<int>{
        cout<<"? "<<st.size()<<" ";
        for(auto &it : st) cout<<it+1<<" ";
        cout<<endl;
        int sz; cin>>sz;
        vi ret(sz); cin>>ret;
        return ret;
    };
    vi dp(n*n+1,1);
    vi pre(n*n+1,-1);
    vi dp2(n*n+1,1);
    vi pre2(n*n+1,-1);
    int itr = n;
    while(itr--){
        auto ret = ask();
        for(auto it = st.rbegin() ; it != st.rend() ; ++it){
            int a = *it;
            auto x = upper_bound(all(ret),a+1);
            if(x != ret.end()){
                if(dp[a] < 1 + dp[*x-1]) pre[a] = *x-1;
                dp[a] = max(dp[a] , 1 + dp[*x-1]);     
            }
        }
        for(auto &it : st){
            auto x = upper_bound(all(ret),it+1);
            if(x != ret.end()){
                if(x != ret.begin() && *prev(x) != it+1){
                    if(dp2[it] < 1 + dp2[*prev(x)-1]) pre2[it] = *prev(x)-1;
                    dp2[it] = max(dp2[it] , 1 + dp2[*prev(x)-1]);
                } 
            } 
            else if(it+1 != ret.back()){
                if(dp2[it] < 1 + dp2[ret.back()-1]) pre2[it] = ret.back()-1;
                dp2[it] = max(dp2[it] , 1 + dp2[ret.back()-1]);
            }  
        }
        for(auto &it : ret) st.erase(it-1);
        if(st.empty()) break;
    }

    vi res;
    if(*max_element(all(dp)) >= n+1){
        int x = max_element(all(dp)) - dp.begin();
        while(pre[x] != -1){
            res.push_back(x+1);
            x = pre[x];
        }
        res.push_back(x+1);
        if(res[0] > res.back()) reverse(all(res));
    }else{
        int x = max_element(all(dp2)) - dp2.begin();
        while(pre2[x] != -1){
            res.push_back(x+1);
            x = pre2[x];
        }
        res.push_back(x+1);
        if(res[0] > res.back()) reverse(all(res));
    }
    assert(res.size() >= n+1);
    cout<<"! ";
    for(int i = 0 ;i <  n+1 ; i++) cout<<res[i]<<" ";
    cout<<endl;

}

int main() {
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