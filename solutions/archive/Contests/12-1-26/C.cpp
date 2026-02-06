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
    int n,p,s; cin>>n>>p>>s;
    vi a(n),b(n); cin>>a>>b;
    vi idx(n); iota(all(idx),0);
    sort(all(idx),[&](int x,int y){
        return a[x] > a[y];
    });
    priority_queue<pair<int,int>>diff,sport;
    vi ty(n);
    int res = 0;
    for(int i = 0;i < p ; i++){
        int x = idx[i];
        diff.push({b[x]-a[x],x});
        ty[x] = 1;
        res += a[x];
    }
    for(int i = p; i  < n ; i++){
        int x = idx[i];
        sport.push({b[x],x});
    }
    int ptr = p;
   
    for(int i = 0;i < s ; i++){
        int x = idx[ptr];
        while(ty[x]!=0){
            ptr++;
            x = idx[ptr];
        } 
        while(ty[sport.top().second]!=0) sport.pop();
        int opt1 = diff.top().first + a[x];
        int opt2 = sport.top().first;
        if(opt1 > opt2){
            ty[diff.top().second] = 2;
            ty[x] = 1;
            diff.pop();
            diff.push({b[x]-a[x],x});
            ptr++;
            res += opt1;
        }else{
            ty[sport.top().second] = 2;
            sport.pop();
            res += opt2;
        }
    }
    cout<<res<<ln;
    for(int i =0 ;i <n ; i++){
        if(ty[i] == 1) cout<<i+1<<" ";
    }
    cout<<ln;
    for(int i =0 ;i <n ; i++){
        if(ty[i] == 2) cout<<i+1<<" ";
    }
    cout<<ln;
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