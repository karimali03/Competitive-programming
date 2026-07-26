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
    string s; cin>>s;
    char ch; cin>>ch;
    vi blks;
    for(int i = 0;i < n ;){
        int cnt = 0;
        while(i < n && s[i] != ch){
            cnt++;
            i++;
        }
        blks.push_back(cnt);
        cnt = 0;
        while(i < n && s[i] == ch){
            cnt++; i++;
        }
        blks.push_back(cnt);
    }
    blks.push_back(0);
    int sz = blks.size();
    int xr = 0;
    int sum = 0;
    for(int i = 0;i < (int)blks.size() ; i+=2){
        xr ^= blks[i];
        sum += blks[i];
    } 
    int res = 0;
    if(xr){
        res = 1 + 24 * sum;
    }
    for(int i = 0;i < sz ; i+=2){
        if(blks[i] == 0) continue;
        for(int x = 0 ; x < blks[i] ; x++){
            int l = x;
            int r = blks[i] - x - 1;
            int cur = xr ^ blks[i] ^ l ^ r;
            if(cur) res++;
        }
    }
    for(int i = 1 ; i < sz ; i+=2){
        if(blks[i] == 0) continue;
        if( (xr^1) && blks[i] > 2){
            res += 25 * (blks[i] - 2);
        }
        if(blks[i] == 1){
            int cur = xr ^ blks[i-1] ^ (blks[i-1] + 1);
            if(i+1 < sz) cur = cur ^ (blks[i-1] + 1) ^ blks[i+1] ^ (blks[i-1]+blks[i+1]+1);
            if(cur) res += 25;
        }else{
            if(i+1 < sz){
                int cur = xr ^ blks[i+1] ^ (blks[i+1]+1);
                if(cur) res += 25;
            }
            if(i-1 >= 0){
                int cur = xr ^ blks[i-1] ^ (blks[i-1]+1);
                if(cur) res += 25;
            }
        }
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