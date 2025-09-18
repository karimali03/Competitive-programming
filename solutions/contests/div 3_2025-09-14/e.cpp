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


int compute_mex(vector<int> &values) {
    int n = values.size();
    vector<bool> seen(n + 1, false);
 
    for (const auto &x : values)
        if (x <= n)
            seen[x] = true;
 
    int mex = 0;
 
    while (seen[mex]) mex++;
 
    return mex;
}

void solve(int test_case) {
    int n,k; cin>>n>>k;
    vi cnt(n+1);
    vi v(n); cin>>v;
    f(i,0,n) cnt[v[i]]++;
    int cn = min(3ll , k);
    int a = -1,b = -1,c = -1;
    while(cn--){
        int mex = compute_mex(v);
        c = mex;
        if(a != -1 && b == -1) b = mex;
        a = mex;
        for(int i = 0 ; i < n ; i++){
            if(v[i] > mex){
                v[i] = mex;
            }
            else if(cnt[v[i]] > 1) v[i] = mex;
        }
        f(i,0,n+1) cnt[i] = 0;
        f(i,0,n) cnt[v[i]]++;
    }
    if(k <= 3){
        int sum = 0;
        f(i,0,n) sum+=v[i];
        cout<<sum<<ln;
        return;
    }
  //  cout<<a<<" "<<b<<" "<<c<<ln;
  //  cout<<v<<ln;
    int sum = 0;
    if(k&1) sum += c * cnt[c];
    else sum += b * cnt[c];
    f(i,0,n) if(cnt[v[i]] == 1) sum+=v[i];
    cout<<sum<<ln;

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