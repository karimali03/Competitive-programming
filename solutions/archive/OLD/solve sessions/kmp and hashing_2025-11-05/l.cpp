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

vector<int> preifx_function(string &s){
    int n = s.size();
    vi pi(n);
    for(int i = 1; i < n ; i++){
        int j = pi[i-1];
        while(j>0 && s[i]!=s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> find_substr(string &s,string &t){
    string cur = s + '#' + t;
    int n = s.size();
    int m = t.size();
    int sz = cur.size();
    cout<<cur<<ln;
    auto pi = preifx_function(cur);
    vi ret;
    for(int i = n+1 ; i < sz ; i++){
        if(pi[i] == n){
            ret.push_back(i - 2*n);
        }
    }
    cout<<ln;
    cout<<ret<<ln;
    return ret;
}

vector<int> find_substr(string &s,string &t){
    string cur = s + '#' + t;
    int n = s.size();
    int m = t.size();
    int sz = cur.size();
    auto pi = preifx_function(cur);
    vi ret;
    for(int i = n+1 ; i < sz-1 ; i++){
        if(pi[i] == n){
            if(i-2*n > 0) ret.push_back(i - 2*n);
        }
    }
    return ret;
}

void solve(int test_case) {
    int n; cin>>n;
    vector<vector<string>>str(n,vector<string>(n));
    vii len(n,vi(n));
    for(int i = 0;i < n;i++){
        for(int j=0;j<n;j++){
            cin>>str[i][j];
            len[i][j] = str[i][j].size();
        }
    }
    f(i,0,n) f(j,0,n){
        if(len[i][j] != len[j][i]){
            cout<<"NONE\n"; return;
        }
    }
    if(n>2){
        vi ans(n);
        ans[0] = len[0][1] + len[0][2] - len[1][2];
        if(ans[0] <= 0 || ans[0]%2){
            cout<<"NONE\n"; return;
        }
        ans[0]/=2;
        for(int i = 1 ; i < n ; i++){
            ans[i] = len[0][i] - ans[0];
            if(ans[i] <= 0){
                cout<<"NONE\n"; return;
            }
        }

        f(i,0,n) f(j,0,n) if(i != j){
            if(len[i][j] != ans[i] + ans[j]){
                cout<<"NONE\n"; return;
            }
        }
        vector<set<string>>idx(n);
        for(int i = 0 ; i < n ; i++){
            for(int j = 0;j < n ; j++){
                if(i == j) continue;
                idx[i].insert(str[i][j].substr(0,ans[i]));
                idx[j].insert(str[i][j].substr(ans[i],ans[j]));
            }
        }

        f(i,0,n) if(idx[i].size() > 1){
            cout<<"NONE\n"; return;
        }
        cout<<"UNIQUE"<<ln;
        cout<<str[0][1].substr(0,ans[0])<<ln;
        for(int i = 1; i < n ;i++){
            cout<<str[0][i].substr(ans[0],ans[i])<<ln;
        }
    }
    else{
        string t = str[0][1] + str[0][1];
        auto ret = find_substr(str[1][0] , t);
        if(ret.empty()) cout<<"NONE\n";
        else if(ret.size() > 1) cout<<"MANY\n";
        else{
            cout<<"UNIQUE\n";
            int s1 = ret[0] , s2 = (int)t.size() - s1 - len[0][1];
            cout<<t.substr(0,s1)<<ln;
            cout<<t.substr(s1+len[0][1],s2)<<ln;
        }
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