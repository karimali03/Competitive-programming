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
    static const int MAX_BITS = 18;
    struct node {
        int nxt[10];
        bool leaf;
        int cnt;
        node() {
            leaf = false;
            cnt = 0;
            memset(nxt,sizeof(nxt),-1);
        }
    };
    vector<node> child;

    Trie() {
        child.push_back(node());
    }

    void insert(string &s){
        int cur = 0;
        for(int i = MAX_BITS ; i >= 0 ; i--){
            int digit = s[i]-'0';
            if(child[cur].nxt[digit] == -1){
                child[cur].nxt[digit] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[digit];
            child[cur].cnt++;
        }
    }
   
    bool search(int num){
        int cur = 0;
        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(child[cur].nxt[bit] == -1) return false;
            cur = child[cur].nxt[bit];
        }
        return true; 
    }

    int find_max(int num){
        int ret = 0;
        int cur = 0;
        for(int sh = MAX_BITS ; sh >= 0 ; sh--){
            if (cur == -1) break; 
            int bit = (num >> sh)&1;
            
            if(child[cur].nxt[1-bit] != -1){
                ret |= (1 << sh);
                cur = child[cur].nxt[1-bit];
            }else{
                cur = child[cur].nxt[bit];
            }
        }
        return ret;
    }


    int find_min(int num){
        return 0ll;
    }

};


void solve(int test_case) {

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