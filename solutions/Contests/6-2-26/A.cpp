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

void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    priority_queue<int>q;
    for(int i=0;i<m;i++){
        int x; cin>>x;
        q.push(x);
    }
    if(k == 1){
        YES; return;
    }
    if(k > m){
        NO; return;
    }
    
    int rem = n;
    while(!q.empty()){
        auto x = q.top(); q.pop();
        rem -=x;
        if(rem < (x-1)*(k-1)){
            NO; return;
        }
        bool lst = false;
        if(rem <= x*(k-1)) lst = true;
        if(lst){
            int tag = (x-1)*(k-1);
            while(!q.empty()){
                auto tp = q.top(); q.pop();
                if(tp == x) tag = tag - (x-1);
                else {
                    int use = min(tag , tp);
                    tag -= use;
                    if(tp - use > 0) q.push(tp-use);
                }
            }
            if(tag != 0){
                NO; return;
            }
        }else{
            int tag = x*(k-1);
            while(tag > 0){
                int tp = q.top(); q.pop();
                int use = min(tag , tp);
                if(tp-use > 0) q.push(tp-use);
                tag -= use; rem -= use;
            }
        }
    }
    YES;


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