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
    int n; cin>>n;
    vi v(n); cin>>v;
    if(count(all(v),0) == n){
        cout<<0<<ln; return;
    }
    int neg = 0,pos=0;
    f(i,0,n){
        if(v[i] > 0) pos++;
        else if(v[i] < 0) neg++;
    }

    vii op;
    if(neg < pos){
        int mx = max_element(all(v)) - v.begin();
        while(v[mx] < 20){
            v[mx] += v[mx];
            op.push_back({mx,mx});
        }
        for(int i = 0 ; i < n ; i++){
            if(v[i] < 0){
                op.push_back({i,mx});
                v[i] += v[mx];
            }
        }
        for(int i = 1 ; i < n ; i++){
            if(v[i] < v[i-1]){
                op.push_back({i,i-1});
                v[i] += v[i-1];
            }
        }
    }else{
        int mn = min_element(all(v)) - v.begin();
        while(v[mn] > -20){
            v[mn] += v[mn];
            op.push_back({mn,mn});
        }
        for(int i = 0 ; i < n ; i++){
            if(v[i] > 0){
                op.push_back({i,mn});
                v[i] += v[mn];
            }
        }
        for(int i = n-1 ; i >= 1 ; i--){
            if(v[i-1] > v[i]){
                op.push_back({i-1,i});
                v[i-1] += v[i];
            }
        }
    }


    cout<<op.size()<<ln;
    for(auto &it : op){
        cout<<it[0]+1<<" "<<it[1]+1<<ln;
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