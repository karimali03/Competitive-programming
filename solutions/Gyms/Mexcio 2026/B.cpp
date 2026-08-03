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
    vector<pair<int,int>>X(n),Y(n);
    for(int i = 0;i < n ; i++){
        int x,y; cin>>x>>y;
        X[i] = {x+y,i};
        Y[i] = {x-y,i};
    }
    if(n <= 3){
        cout<<0<<ln;
        return;
    }

    sort(all(X));
    sort(all(Y));
    vi ch = {0,1,n-1,n-2,0,1,n-1,n-2};
    int mn = max(X[n-1].first - X[0].first , Y[n-1].first - Y[0].first);
    for(int i = 0;i < 8 ; i++){
        for(int j = 0; j < 8 ; j++){
            if(i == j) continue;
            int lx = 0,rx = n-1;
            int ly = 0,ry = n-1;
            int idx1 = -1 , idx2 = -1;
            if(i < 4) idx1 = X[ch[i]].second;
            else idx1 = Y[ch[i]].second;
            if(j < 4) idx2 = X[ch[j]].second;
            else idx2 = Y[ch[j]].second;
            while(X[lx].second == idx1 || X[lx].second == idx2){
                lx++;
            }
            while(X[rx].second == idx1 || X[rx].second == idx2){
                rx--;
            }
            while(Y[ly].second == idx1 || Y[ly].second == idx2){
                ly++;
            }
            while(Y[ry].second == idx1 || Y[ry].second == idx2){
                ry--;
            }
            mn = min(mn , max(X[rx].first-X[lx].first,Y[ry].first-Y[ly].first));
        }
    }
    cout<<mn<<ln;
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