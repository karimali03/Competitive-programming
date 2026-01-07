#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3", "unroll-loops")

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


const int N = 1005;
int dp[2][N][N];
int cnt[2][N][N]{};
int v[N][N];
int build[2][N][N]{};
int n;
int rec(int i,int j,int idx) {
        if(i == n-1 && j == n-1) return cnt[idx][i][j];
        int &ret = dp[idx][i][j];
        return ret;
};

void solve(int test_case) {
    cin>>n;
    pair<int,int> zero = {-1,-1};
    for(int i = 0 ; i < n ; i++){
        for(int j = 0;  j < n ; j++){
            cin>>v[i][j];
            if(v[i][j] == 0){
                zero = {i,j};
                continue;
            } 
            while (v[i][j]%2 == 0) v[i][j]/=2,cnt[0][i][j]++;
            while(v[i][j] % 5 == 0) v[i][j]/=5,cnt[1][i][j]++;
        }
    }
  

    for(int idx = 0 ; idx < 2 ; idx++){
        for(int i = n-1 ; i >= 0 ; i--){
            for(int j = n-1 ;j >= 0 ; j--){
                 int &ret = dp[idx][i][j] = INT32_MAX;
                 if(i+1 < n){
                     int ch1 = cnt[idx][i][j] + rec(i+1,j,idx);
                     if(ret > ch1){
                        ret = ch1;
                        build[idx][i][j] = 1; // D
                     }
                 } 
                 if(j+1 < n){
                    int ch1 = cnt[idx][i][j] + rec(i,j+1,idx);
                     if(ret > ch1){
                        ret = ch1;
                        build[idx][i][j] = 2; // R
                     }
                 } 
            }
        }
    }
    int mn2 = dp[0][0][0];
    int mn5 = dp[1][0][0];
    if(zero.first != -1 && min(mn2,mn5) >= 1){
        cout<<1<<ln;
        string res;
        int curi = 0 , curj = 0;
        while (curi < zero.first ){
            res.push_back('D'); curi++;
        }
        while (curj < n-1){
            res.push_back('R'); curj++;
        }
        while (curi < n-1){
            res.push_back('D'); curi++;
        }
        cout<<res<<ln;
        return;
    }
    string res;
    if(mn2 < mn5){
        int i = 0,j = 0;
        while (i != n-1 || j != n-1){
            if(build[0][i][j] == 1){
                res.push_back('D'); i++;
            }
            else res.push_back('R'),j++;
        }
        cout<<mn2<<ln;
        cout<<res<<ln;
    }else{
        int i = 0,j=0;
        while (i != n-1 || j != n-1){
            if(build[1][i][j] == 1){
                res.push_back('D'); i++;
            }
            else res.push_back('R'),j++;
        }
        cout<<mn5<<ln;
        cout<<res<<ln;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}