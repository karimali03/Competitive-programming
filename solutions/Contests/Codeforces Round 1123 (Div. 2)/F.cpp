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
    static const int MAX_BITS = 30;

    struct Node {
        int nxt[2];
        int cnt;
        bool leaf;
        vector<int>idx;
        Node() {
            nxt[0] = nxt[1] = -1;
            cnt = 0;
            leaf = false;
        }
    };

    vector<Node> nodes;

    // n = expected number of inserted values.
    Trie(int n = 0) {
        nodes.reserve(1 + n * (MAX_BITS + 1));
        nodes.push_back(Node());
    }

    void clear() {
        nodes.clear();
        nodes.push_back(Node());
    }

    int size() const {
        return nodes[0].cnt;
    }

    bool empty() const {
        return size() == 0;
    }

    // Returns true if this edge has at least one active value.
    bool has(int cur, int bit) const {
        int to = nodes[cur].nxt[bit];
        return to != -1 && nodes[to].cnt > 0;
    }

    void insert(int value,int id) {
        int cur = 0;
        nodes[cur].cnt++;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            int b = (value >> bit) & 1;

            if (nodes[cur].nxt[b] == -1) {
                nodes[cur].nxt[b] = nodes.size();
                nodes.push_back(Node());
            }

            cur = nodes[cur].nxt[b];
            nodes[cur].cnt++;
        }
        nodes[cur].idx.push_back(id);
        nodes[cur].leaf = true;
    }
    /*
        Returns the k-th smallest value of:

            value ^ stored_value

        k is 0-indexed.
        Duplicates are counted.

        Returns -1 if k is invalid.
    */
    pair<int,vi> kth_xor(int value, int k) const {
        if (k < 0 || k >= size())
            return {-1,{}};

        int cur = 0;
        int result = 0;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            int b = (value >> bit) & 1;

            /*
                To make XOR bit 0:
                stored_bit must equal value_bit.
            */
            int zero_branch = nodes[cur].nxt[b];

            int zero_count =
                zero_branch == -1
                ? 0
                : nodes[zero_branch].cnt;

            if (k < zero_count) {
                // kth value is in XOR-bit-0 branch.
                cur = zero_branch;
            } else {
                // Skip all XOR-bit-0 values.
                k -= zero_count;

                result |= (1LL << bit);

                cur = nodes[cur].nxt[b ^ 1];
            }
        }

        return {result , nodes[cur].idx};
    }
};

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v; 
    sort(all(v));
    vi res(10);
    int en = 0;
    for(int op = 0;op < 10 ; op++){
        res[op] = v[n-1] - v[0];
        if(res[op] == 0){
            en = op; break;
        }
        Trie st(n);
        vi cur(n,1);
        set<pair<int,int>>s;
        for(int i=0;i<n;i++) st.insert(v[i],i);
        priority_queue<tuple<int,int,vi>,vector<tuple<int,int,vi>>,greater<>>q;
        for(int i=0;i<n;i++){
            s.insert({i,i});
            auto X = st.kth_xor(v[i],cur[i]);
         //   cout<<i<<" "<<v[i]<<" "<<X.first<<" -- "<<X.second<<ln;
            q.push({X.first,i,X.second});
        }
        vi vv(n);
        for(int i = 0 ;i < n ; ){
            auto [val,id,X] = q.top(); q.pop();
            cur[id] += X.size();
            while(i < n && !X.empty()){
                if(s.count(minmax(id,X.back()))){
                    X.pop_back(); continue;
                }
                s.insert(minmax(id,X.back()));
          //      cout<<id<<" "<<X.back()<<" "<<val<<ln;
                vv[i++] = val;
            }
            auto nv = st.kth_xor(v[id],cur[id]);
            if(nv.first != -1) q.push({nv.first,id,nv.second});
        }
        v = vv;
     //   cout<<" ------- \n";
    }

    while(q--){
        int x; cin>>x;
        if(x >= en) cout<<res[en]<<ln;
        else cout<<res[x]<<ln;
    }
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