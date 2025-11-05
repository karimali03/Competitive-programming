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

const int S = 505;
const int N = 35;
int dp[N][S];
int x;
int rec(int rem,int sum){
    if(rem == 0) return sum == x;
    int &ret = dp[rem][sum];
    if(~ret) return ret;
    ret = 0;
    for(int i = 1 ; i <= rem ; i++) ret |= rec(rem-i,sum + (i*(i+1)/2) );
    return ret;
}

vi res;
void build(int rem,int sum){
    if(rem == 0) return;
    int opt = rec(rem,sum);
    for(int i = 1 ; i <= rem;  i++){
        if(opt == rec(rem-i,sum + (i*(i+1)/2))){
            res.push_back(i);
            build(rem-i,sum + (i*(i+1)/2));
            return;
        }
    }
}
void solve(int test_case) {
    int n,k; cin>>n>>k;
    int a = n*(n+1)/2;
    x = n*(n+1)/2 - k;
    f(i,0,n+1) f(j,0,a) dp[i][j] = -1;
    if(rec(n,0)){
        res.clear();
        build(n,0);
        vi v(n);
        f(i,0,n) v[i] = i+1;
        for(auto x : res){
            stack<int>st;
            while(x--){
                st.push(v.back());
                v.pop_back();
            }
            while(!st.empty()){
                cout<<st.top()<<" ";
                st.pop();
            }
        }
        cout<<ln;
    }else{
        cout<<0<<ln;
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