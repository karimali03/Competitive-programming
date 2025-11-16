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


vector<int> prefix_function(string &s){
    int n = s.size();
    vector<int> pi(n);
    for(int i = 1 ; i < n ; i++){
        int j = pi[i-1];
        while(j>0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
/*
current match length is k, I add character c, what will my new match length be?
way to "de-amortize" the standard KMP prefix function calculation.
*/
vii prefix_function_automaton(string &s){
    int n = s.size();
    auto pi = prefix_function(s);
    vii aut(n,vi(26));
    aut[0][s[0]-'a'] = 1;
    for(int i = 1 ;i < n ; i++){
        for(int j = 0; j < 26 ; j++){
            if(j == (s[i]-'a')) aut[i][j] = i+1;
            else aut[i][j] = aut[pi[i-1]][j];
        }
    }
    return aut;
}
void solve(int test_case) {
    string s; cin>>s;
    int n = s.size();
    auto pi = prefix_function(s);
    vii aut(n,vi(26));
    aut[0][s[0]-'a'] = 1;
    for(int i = 1; i < n ; i++){
        for(int j = 0; j < 26 ; j++){
            if(j == (s[i]-'a')) aut[i][j] = i+1;
            else aut[i][j] = aut[pi[i-1]][j];
        }
    }

    int q; cin>>q;
    while(q--){
        string x; cin>>x;
        s+=x;
        int m = x.size();
        for(int i = n ; i < n+m;  i++){
            aut.push_back(vector<int>(26));
            for(int j = 0; j < 26 ; j++){
                if(j == (s[i]-'a')) aut[i][j] = i+1;
                else aut[i][j] = aut[pi[i-1]][j];
            }
            pi.push_back(aut[pi[i-1]][s[i]-'a']);
            cout<<pi.back()<<" ";
        }
        cout<<ln;
        while(m--) s.pop_back(),pi.pop_back(),aut.pop_back();
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