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

vector<int> prefix_function(const string &s){
    int n = s.size();
    vector<int> pi(n);
    int j = 0;

    for(int i = 1; i < n; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }

    return pi;
}

vii prefix_function_automaton(const string &s){
    int n = s.size();
    vii aut(n+1, vi(26));

    if(n == 0) return aut;

    auto pi = prefix_function(s);

    aut[0][s[0]-'a'] = 1;

    for(int i = 1; i < n; i++){
        for(int c = 0; c < 26; c++){
            if(c == s[i]-'a')
                aut[i][c] = i+1;
            else
                aut[i][c] = aut[pi[i-1]][c];
        }
    }

    // allow continuing after a full match (overlapping matches)
    for(int c = 0; c < 26; c++)
        aut[n][c] = aut[pi[n-1]][c];

    return aut;
}

const int N = 12;
const int M = 55;
int dp[1<<N][M];
int vis[1<<N][M]{};
int see = 0;
int n,m;    
string s[N];
vector<vector<int>> aut;
string l,r;

int nxt[N][M];
int gain[N][M];
int rec(int msk,int j){
    if(vis[msk][j] == see) return dp[msk][j];
    vis[msk][j] = see;
    if(co(msk) == n){
        int nj = j;
        int cur = 0;
        for(auto &c : r){
            nj = aut[nj][c-'a'];
            if(nj == m) cur++;
        }
        return dp[msk][j] = cur;
    }
    int &ret = dp[msk][j];
    ret = 0;
    for(int i = 0;i < n; i++){
        if((msk>>i)&1) continue;
        ret = max(ret , gain[i][j] + rec(msk | (1 << i), nxt[i][j] ));
    }
    return ret;
}

void solve(int test_case) {
    cin>>n;
    f(i,0,n) cin>>s[i];
    string p; 
    cin>>p;
    m = p.size();
    aut = prefix_function_automaton(p);

    for(int i = 0;i < n ; i++){
        for(int j = 0 ; j <= m ; j++){
            int nj = j,cur = 0;
            for(auto &c : s[i]){
                nj = aut[nj][c-'a'];
                if(nj == m) cur++;
            }
            nxt[i][j] = nj; gain[i][j] = cur;
        }
    }

    int mx = 0;
    for(int i = 0;i < n ; i++){
        l = s[i]; r.clear(); 
        for(auto &c : s[i]){
            see++;
            int j = 0,cost = 0;
            for(auto &it : l){
                j = aut[j][it-'a'];
                if(j == m) cost++;
            }
            mx = max(mx , cost + rec((1<<i),j));
            l.erase(l.begin()); r.push_back(c);
        }
        see++; 
        mx = max(mx , rec((1<<i),0));
    }

    cout<<mx<<ln;

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