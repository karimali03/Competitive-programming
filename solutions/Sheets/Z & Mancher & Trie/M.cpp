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

struct PersistentTrie {
    static const int LOG = 30; // for values <= 1e9

    struct Node {
        int nxt[2];
        int cnt;

        Node() {
            nxt[0] = nxt[1] = 0;
            cnt = 0;
        }
    };

    vector<Node> tr;
    vector<int> root;

    PersistentTrie(int n = 0) {
        tr.reserve((n + 5) * (LOG + 2));
        tr.push_back(Node()); // node 0 = null node

        root.assign(n + 1, 0);
    }

    int clone(int node) {
        tr.push_back(tr[node]);
        return (int)tr.size() - 1;
    }

    int insert(int oldRoot, int x) {
        int newRoot = clone(oldRoot);

        int oldNode = oldRoot;
        int newNode = newRoot;

        tr[newNode].cnt++;

        for (int bit = LOG; bit >= 0; bit--) {
            int b = (x >> bit) & 1;

            int oldChild = tr[oldNode].nxt[b];
            int newChild = clone(oldChild);

            tr[newNode].nxt[b] = newChild;

            oldNode = oldChild;
            newNode = newChild;

            tr[newNode].cnt++;
        }

        return newRoot;
    }

    // Build:
    // root[i] contains a[1..i]
    void add(int i, int x) {
        root[i] = insert(root[i - 1], x);
    }

    // max(x ^ a[j]) for j in [l, r]
    int query(int l, int r, int x) {
        int leftRoot = root[l - 1];
        int rightRoot = root[r];

        int ans = 0;

        for (int bit = LOG; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            int want = b ^ 1;

            int L = tr[leftRoot].nxt[want];
            int R = tr[rightRoot].nxt[want];

            if (tr[R].cnt - tr[L].cnt > 0) {
                ans |= (1 << bit);

                leftRoot = L;
                rightRoot = R;
            }
            else {
                leftRoot = tr[leftRoot].nxt[b];
                rightRoot = tr[rightRoot].nxt[b];
            }
        }

        return ans;
    }
};


vector<int> PGE(vector<int> &v){
    int n = v.size();
    vi ret(n,-1);
    stack<int>st;
    for(int i = n-1;i >= 0; i--){
        while(!st.empty() && v[i] >= v[st.top()]){
            ret[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return ret;
}

vector<int> NGE(vector<int> &v){
    int n = v.size();
    vi ret(n,n);
    stack<int>st;
    for(int i = 0;i < n; i++){
        while(!st.empty() && v[i] > v[st.top()]){
            ret[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return ret;
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    auto ng = NGE(v);
    auto pg = PGE(v);
    PersistentTrie st(n+5);
    st.add(1,0);
    vi pre(n+1);
    for(int i = 0;i < n ; i++){
        pre[i+1] = v[i] ^ pre[i];
        st.add(i+2,pre[i+1]);
    }
    int mx = 0;
    for(int i = 0;i < n ; i++){
        int l = pg[i]+1; int r = ng[i]-1;
        if(i-l < r-i){
            // left is smaller
            // l-1 ...... i-1
            for(int x = l-1 ; x <= i-1 ; x++){
                int val = pre[x+1] ^ v[i];
                int cur = st.query(i+2,r+2,val);
                mx = max(mx , cur);
            }
        }else{
            // left is bigger
            for(int x = i ; x <= r ; x++){
                int val = pre[x+1] ^ v[i];
                int cur = st.query(l+1,i+1,val);
                mx = max(mx , cur);
            }
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