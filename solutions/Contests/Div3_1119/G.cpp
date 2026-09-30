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
    int n,k; cin>>n>>k;
    vi a(n); cin>>a;
    vi b(n);
    for(int i = 0;i < n ; i++) b[i] = a[i] - i*k;
    vi pre(n);
    for(int i = 0 ;i  < n ; i++){
        pre[i] = b[i];
        if(i) pre[i] += pre[i-1];
    }
    vi res(n);
    for(int i = 1 ; i < n-1 ; i++){
        int cur = a[i-1] - i*k;
        int l = i+1,r = n-1;
        int ans = i;
        while(l<=r){
            int mid = l + (r-l)/2;
            if(b[mid] >= cur){
                ans = mid; l = mid+1;
            }else{
                r = mid-1;
            }
        }
        res[i] = pre[ans] - pre[i];
        res[i] += (-a[i-1] + i*k) * (ans-i);
    }   
    cout<<res<<ln;
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