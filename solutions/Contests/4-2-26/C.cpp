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
    vector<pair<int,int>>v(k);
    f(i,0,k) cin>>v[i].first;
    f(i,0,k) cin>>v[i].second;
    sort(all(v));
    if(v[0].second > v[0].first){
        NO; return;
    }
    string s = "abc";
    string base = "abc";
    int sum = v[0].second;
    v[0].second -= 3;
    while(v[0].second--){
        s.push_back('c');
    }
    int cur = 0;
    while(s.size() < v[0].first){
        s.push_back(base[cur]);
        cur = (cur+1)%3;
    }
  
    char nxt = 'd';
    for(int i = 1 ; i < k ; i++){
        int len = v[i].first;
        int cnt = v[i].second;
        if(cnt-sum > len-(int)s.size()){
            NO; return;
        }
        int x = sum;
        sum = cnt;
        cnt = cnt - x;

        while(cnt--){
            s.push_back(nxt);
        }
        nxt++;
        while(s.size() < len){
            s.push_back(base[cur]);
            cur = (cur+1)%3;
        }
    }
    YES;
    cout<<s<<ln;
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