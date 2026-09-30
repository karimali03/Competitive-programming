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
#define int ll
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
    static const int LOG = 20;

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

        // node 0 = null node
        tr.push_back(Node());

        // root[i] = trie containing first i inserted values
        root.assign(n + 1, 0);
    }

    // Copy a node from the previous version.
    int clone(int node) {
        tr.push_back(tr[node]);
        return (int)tr.size() - 1;
    }

    // Create a new version by inserting x into oldRoot.
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

    // root[i] contains values added at positions [1..i].
    void add(int i, int x) {
        root[i] = insert(root[i - 1], x);
    }

    // Number of values from range-version [l..r]
    // that go through child 'b' of the current nodes.
    int count_branch(int leftRoot, int rightRoot, int b) {
        int L = tr[leftRoot].nxt[b];
        int R = tr[rightRoot].nxt[b];

        return tr[R].cnt - tr[L].cnt;
    }

    /*
        max(x ^ a[j]), l <= j <= r

        root[r]     contains a[1..r]
        root[l - 1] contains a[1..l-1]

        Their count difference represents exactly a[l..r].
    */
    int max_xor(int l, int r, int x) {
        int LRoot = root[l - 1];
        int RRoot = root[r];

        int ans = 0;

        for (int bit = LOG; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            int want = b ^ 1;

            if (count_branch(LRoot, RRoot, want) > 0) {
                ans |= (1 << bit);

                LRoot = tr[LRoot].nxt[want];
                RRoot = tr[RRoot].nxt[want];
            }
            else {
                LRoot = tr[LRoot].nxt[b];
                RRoot = tr[RRoot].nxt[b];
            }
        }

        return ans;
    }

    int count_gt(int l,int r,int val,int lim){
        if(l > r) return 0;
        int LRoot = root[l - 1];
        int RRoot = root[r];     
        int ans = 0;
        for (int bit = LOG; bit >= 0; bit--) {
            if(LRoot == -1 || RRoot == -1) break;
            int bv = (val >> bit)&1;
            int bl = (lim >> bit)&1;
            int n0 = count_branch(LRoot,RRoot,0);
            int n1 = count_branch(LRoot,RRoot,1);
            int want = 0;
            if(bv && bl){
                want = 0;
            }else if(bv && !bl){
                ans += n0;
                want = 1;
            }else if(!bv && bl){
                want = 1;
            }else{
                ans += n1;
                want = 0;
            }
            if (count_branch(LRoot, RRoot, want) > 0) {
                LRoot = tr[LRoot].nxt[want];
                RRoot = tr[RRoot].nxt[want];
            }
            else {
                LRoot = -1;
                RRoot = -1;
            }
        }
        return ans;
    }

    /*
        min(x ^ a[j]), l <= j <= r
    */
    int min_xor(int l, int r, int x) {
        int LRoot = root[l - 1];
        int RRoot = root[r];

        int ans = 0;

        for (int bit = LOG; bit >= 0; bit--) {
            int b = (x >> bit) & 1;

            if (count_branch(LRoot, RRoot, b) > 0) {
                LRoot = tr[LRoot].nxt[b];
                RRoot = tr[RRoot].nxt[b];
            }
            else {
                ans |= (1 << bit);

                b ^= 1;
                LRoot = tr[LRoot].nxt[b];
                RRoot = tr[RRoot].nxt[b];
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
    for(int i = 0;i < n ;i++) st.add(i+1,v[i]);
    int res = 0;
    for(int i = 0;i < n ; i++){
        int l = pg[i]+1; int r = ng[i]-1;
        if(i-l < r-i){
            // left is smaller
            // l-1 ...... i
            for(int x = l ; x <= i ; x++){
                int lx = (x == i) ? i+1 : i;
                int cur = st.count_gt(lx+1,r+1,v[x],v[i]);
                res += v[i] * cur;
            }
        }else{
            // left is bigger
            for(int x = i ; x <= r ; x++){
                int rx = (x == i) ?  i-1: i;
                int cur = st.count_gt(l+1,rx+1,v[x],v[i]);
                res += v[i] * cur;
            }
        }
    }
    cout<<res<<ln;

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