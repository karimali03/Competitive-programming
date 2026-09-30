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

vector<int> z_function(const string& s) {
    int n = s.length();
    vector<int> z(n);
    // l and r define the "Z-box" (matches the prefix) [l, r]
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        // If i is inside the current Z-box, use previous values to initialize z[i]
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        // Naively extend the match as far as possible
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        // If we have extended past the current Z-box, update the box
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}




struct SegmentTree {
    struct node {
        int mx;
    };

    int n;
    vector<node> tree;

    node neutral = {-1};

    SegmentTree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        tree.assign(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        return {max(a.mx,b.mx)};
    }

    void build(const vector<int> &a) {
        for (int i = 0; i < a.size(); i++)
            tree[n + i] = {a[i]};

        for (int i = n - 1; i; i--)
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int pos, int val) {
        pos += n;
        tree[pos] = {val};

        while (pos >>= 1)
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
    }

    bool check(node &x){
        return true;
    }

    int first(int l, int r) {
        vector<int> left, right;

        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left.push_back(l++);
            if (r & 1) right.push_back(--r);
        }

        reverse(right.begin(), right.end());

        // process segments from left to right
        for (int v : left) {
            if (!check(tree[v])) continue;

            while (v < n) {
                if (check(tree[v << 1]))
                    v <<= 1;
                else
                    v = v << 1 | 1;
            }

            return v - n;
        }

        for (int v : right) {
            if (!check(tree[v])) continue;

            while (v < n) {
                if (check(tree[v << 1]))
                    v <<= 1;
                else
                    v = v << 1 | 1;
            }

            return v - n;
        }

        return -1;
    }


    int last(int l, int r) {
        vector<int> left, right;

        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left.push_back(l++);
            if (r & 1) right.push_back(--r);
        }

        // process segments from right to left
        for (int v : right) {
            if (!check(tree[v])) continue;

            while (v < n) {
                if (check(tree[v << 1 | 1]))
                    v = v << 1 | 1;
                else
                    v <<= 1;
            }

            return v - n;
        }

        reverse(left.begin(), left.end());

        for (int v : left) {
            if (!check(tree[v])) continue;

            while (v < n) {
                if (check(tree[v << 1 | 1]))
                    v = v << 1 | 1;
                else
                    v <<= 1;
            }

            return v - n;
        }

        return -1;
    }

};

void solve(int test_case) {
    int n,q; cin>>n>>q;
    string s; cin>>s;
    vi pi = prefix_function(s);
    vi val;
    int cur = pi[n-1];
    while(cur > 0){
        val.push_back(cur);
        cur = pi[cur-1];
    }
    sort(all(val));
    auto z = z_function(s);
    z[0] = n;
    for(int i = 1 ; i < n ; i++){
        auto len = upper_bound(all(val),z[i]);
        if(len == val.begin()) z[i] = 0;
        else z[i] = *prev(len);
    }
    vi res(n);
    for(int i =0 ;i < n ; i++){
        res[i] = i + z[i];
    }
    while(q--){
        int l,r; cin>>l>>r; l--,r--;
        if(l > r) swap(l,r);
        int res = st.query(0,l,r);
        int x = r - res + 1;
        cout<<*lower_bound(all(val),x)<<ln;
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