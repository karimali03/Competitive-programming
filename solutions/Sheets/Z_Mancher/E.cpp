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

struct Trie {
    struct node {
        map<int,int>nxt;
        bool leaf;
        int cnt;
        node() {
            leaf = false;
             cnt = 0;
        }
    };
    vector<node> child;

    Trie() {
        child.push_back(node());
    }

    void insert(string &s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!child[cur].nxt.count(idx)) {
                child[cur].nxt[idx] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[idx];
            child[cur].cnt++;
        }
        child[cur].leaf = true;
    }
    int calc(const string &s) {
        int cur = 0;
        stack<pair<int,int>>st;
        for(int i = 0;i < (int)s.size() ; i++){
            int idx = s[i] - 'a';
            int l = child[cur].leaf , r = 0;
            for(int j=0;j<idx;j++) if(child[cur].nxt.count(j)) l += child[child[cur].nxt[j]].cnt;
            for(int j=idx+1;j<26;j++) if(child[cur].nxt.count(j)) r += child[child[cur].nxt[j]].cnt;
           // cout<<l<<" "<<r<<ln;
            cur = child[cur].nxt[idx];
            if(i == (int)s.size()-1) r += child[cur].cnt-1;
            st.push({l,r});
        }
        st.push({0,0});
        int res = 1e9;
        int l = 0 , r = 0;
        int sz = s.size();
        while(!st.empty()){
            auto [a,b] = st.top();
            l += a , r += b;
            res = min({res , sz + 1 + l , sz + 2 + r});
            st.pop(); sz--;
        }
        return res;
    }
};

void solve(int test_case) {
    int n; cin>>n;
    vector<string> s(n);
    f(i,0,n) cin>>s[i];
    Trie st;
    f(i,0,n) st.insert(s[i]);
    for(int i = 0;i < n; i++){
        int res = st.calc(s[i]);
        cout<<res<<" ";
    }
    cout<<ln;
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