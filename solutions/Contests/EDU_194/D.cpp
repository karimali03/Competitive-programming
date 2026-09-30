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
       vector<pair<int,int>>cur;
       for(int i = 0;i < n ; ){
            char c = s[i]; int cnt = 0;
            while(i < n && s[i] == c){
                i++,cnt++;
            }
            if(c == '0') cur.push_back({cnt,0});
            else if(c == '+') cur.push_back({cnt,1});
            else cur.push_back({cnt,2});
       }
       if(s[0] == '0'){
            NA; return;
       }
       int sz = cur.size();
       for(int i = 0;i < sz ; i++){
            if(cur[i].first > 1 && cur[i].second == 0){
                NA; return;
            }
       }
       int mx = 0;
       int sum = 0;
       for(int i = 0; i < sz ; i++){
            if(cur[i].second == 0){
                mx = max(mx , sum); 
                sum = 0;
                continue;
            }
            mx = max(mx , sum + 1);
            if(cur[i].first&1){
                sum = 1;
                continue;
            } 
            if(i != sz-1){
                if(cur[i].first == 2){
                    if(sum+1 <= 1){
                        sum = 1; 
                    }else{
                        if(cur[i+1].second == 0) sum = 2;
                        else{
                            sum = 1;
                            mx = max(mx , 3ll);
                        }
                    }
                }else sum = 1;
                mx = max(mx , 2ll);
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