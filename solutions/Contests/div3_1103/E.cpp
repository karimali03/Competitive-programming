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


const int N = 6005;
bool mp[N][N];
int frq[N];


void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    
    for(int i = 0;i <= n ; i++){
        for(int j = i ; j <= n ; j++) mp[i][j]= false;
        frq[i] = 0; 
    }
    for(int i = 0;i < n ; i++){
        int miss = 0;
        int mn = v[i] , mx = v[i];
        mp[mn][mx] = true;
        frq[v[i]]++;
        for(int j = i+1 ; j < n ; j++){
            if(frq[v[j]] == 1) break;
            if(v[j] < mn) miss += (mn-v[j]-1); 
            else if(v[j] > mx) miss += (v[j]-mx-1);
            else miss--;
            frq[v[j]]++;
            mn = min(mn , v[j]);
            mx = max(mx , v[j]);
            if(miss == 0){
                mp[mn][mx] = true;
            } 
        }
        for(int j = i; j < n ; j++){
            frq[v[j]] = 0;
        }
    }
 
    int mx = 0;
    for(int l = 1 ; l <= n ; l++){  
        for(int r = l; r <= n ; r++){ 
          if(2*r-l+1 <= n){
                if(mp[l][r] && mp[r+1][2*r-l+1]){
                    mx = max(mx , r-l+1);
                }
            }
        }
    }
    cout<<mx<<ln;
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