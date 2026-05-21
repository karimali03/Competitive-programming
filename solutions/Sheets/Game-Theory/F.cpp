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


const int N = 18;
int dp[1<<N][N][2];
void solve(int test_case) {
    int n; cin>>n;
    vector<pair<int,int>>a(n);
    string s;
    getline(cin,s);  
    f(i,0,n){
        getline(cin, s);
        a[i] = {s[0]-'a',s.back()-'a'};
    }   
    int m; cin>>m;
    getline(cin,s); 
    vector<pair<int,int>>b(m);
    f(i,0,m){
        getline(cin, s);
        b[i] = {s[0]-'a',s.back()-'a'};
    }  
    vii nxt(n+m);
    f(i,0,n){
        f(j,0,m){
            if(a[i].second == b[j].first) nxt[i].push_back(j+n);
            if(b[j].second == a[i].first) nxt[j+n].push_back(i);
        }
    }
    function<int(int,int,int)> rec = [&](int x,int prv,int ch) -> int{
        int &ret = dp[x][prv][ch];
        if(~ret) return ret;
        bool win = 0;
        for(auto &it : nxt[prv]){
            if((x>>it)&1) continue;
            win |= ( rec(x|(1<<it),it,1-ch) == ch);
        }
        return ret = win ? ch : 1-ch;
    };
    bool win = 0;
    for(int i = 0;i < n ; i++){
        memset(dp,-1,sizeof dp);
        if(rec((1<<i),i,1) == 0){
            win = 1; break;
        }
    }
    cout<<"Game "<<test_case<<": ";
    if(win) cout<<"player1\n";
    else cout<<"player2\n";
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