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


struct Trie {
    struct node {
        unordered_map<int,int>nxt;
        bool leaf;
        pair<int,int>cnt;
        node() {
            leaf = false;
            cnt = {0,0};
        }
    };
    vector<node> child;

    Trie() {
        child.push_back(node());
    }

    void insert(string &s) {
        int cur = 0;
        int sz = s.size();
        for (char c : s) {
            int idx = c - 'a';
            if (!child[cur].nxt.count(idx)) {
                child[cur].nxt[idx] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[idx];
            child[cur].cnt.first++;
            child[cur].cnt.second+=sz;
        }
        child[cur].leaf = true;
    }

    int calc(string &s,int all,int n){
        int sz = s.size();
        int ret = 0 , cur = 0;
        for(int i = 0 ; i < sz ; i++){
            auto idx = s[i] - 'a';
            if(!child[cur].nxt.count(idx)){
                if(i == 0) ret += all + sz * n;
                return ret;
            } 
            cur = child[cur].nxt[idx];
            auto [frq,sum] = child[cur].cnt;
            ret += sum - frq * (i+1) + (sz-i-1) * frq;
            if(i) ret -= (sum - frq * i + (sz - i) * frq);
            if(i == 0) ret += (all - sum) + sz * (n - frq);
        }
        return ret;
    }

    bool word_exist(const string &s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!child[cur].nxt.count(idx)) return false;
            cur = child[cur].nxt[idx];
        }
        return child[cur].leaf;
    }

    bool prefix_exist(const string &s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!child[cur].nxt.count(idx)) return false;
            cur = child[cur].nxt[idx];
        }
        return true;
    }
};



void solve(int test_case) {
    int n; cin>>n;
    vector<string>v(n);
    int sum = 0;
    Trie st;
    for(int i = 0 ; i< n ; i++){
        cin>>v[i];
        sum+=(int)v[i].size();
        st.insert(v[i]);
    }
    int res = 0;
    for(int i = 0 ; i < n ; i++){
        reverse(all(v[i]));
        res += st.calc(v[i],sum,n);
    }
    cout<<res<<ln;
    
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