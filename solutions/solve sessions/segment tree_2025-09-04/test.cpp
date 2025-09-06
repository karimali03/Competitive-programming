#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rand_range(ll l, ll r) { return l + (ull) rng() % (r - l + 1); }
void shuffle(vector<int> &v) { shuffle(v.begin(), v.end(), rng); }
char rand_char() { return 'a' + rand_range(0, 25); }

string rand_string(int len) {
    string s;
    for (int i = 0; i < len; ++i)
        s += rand_char();
    return s;
}

vector<int> rand_permutation(int n) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    shuffle(v);
    return v;
}

vector<int> rand_vector(int n, int l, int r) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        v[i] = rand_range(l, r);
    return v;
}

vector<pair<int, int>> rand_graph(int n, int m, bool directed = false) {
    set<pair<int, int>> edges;
    while ((int)edges.size() < m) {
        int u = rand_range(1, n);
        int v = rand_range(1, n);
        if (u == v) continue;
        if (!directed && u > v) swap(u, v);
        edges.emplace(u, v);
    }
    return vector<pair<int, int>>(edges.begin(), edges.end());
}

struct TestCase {
    int n,q;
    vector<int> a;
    vector<array<int,3>>qu;
    TestCase(int n,int q,vector<int>&a,vector<array<int,3>> &qu):n(n),q(q),a(a),qu(qu){};
};

TestCase generate_input() {
    int n = 10;
    int q = 20;
    vector<int>a(n);
    vector<array<int,3>>qu(q);
    for(int i = 0 ; i < q ; i++){
        if(i < 2) qu[i][0] = 1;
        else qu[i][0] = 2;
      //  qu[i][0] = rand_range(1,2);
        qu[i][1] = rand_range(1,n);
        qu[i][2] = rand_range(1,n);
    }
    TestCase tc(n,q,a,qu);
    return tc;
}



int sum(int n){
    return n*(n+1)/2;
}


struct SegmentTree {
    struct node {
        int val;
    };
    
    vector<node> tree;
    vector<pair<int,int>> lazy;
    node neutral = {0};
    pair<int,int> no_operation = {0,0};
    
    int n;
    int sz;

    SegmentTree(int size) {
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
        lazy.resize(2 * n, no_operation);
    }

    node merge(const node &a, const node &b) {
        return {a.val + b.val}; // Change operation if needed
    }

    void push(int v, int tl, int tr , int deg = 2) {
        if(deg == 0) return;
        if (lazy[v] != no_operation) { // if there is a pending operation
            tree[v].val += (tr - tl + 1) * lazy[v].first + lazy[v].second * sum(tr-tl+1);
        }
        if (tl != tr) {
            if(lazy[v] != no_operation) { // propagate the lazy value to children
                    lazy[v * 2 + 1].first += lazy[v].first;
                    lazy[v * 2 + 1].second += lazy[v].second;
                    lazy[v * 2 + 2].first += lazy[v].first + ((tl + tr) / 2 - tl + 1); 
                    lazy[v * 2 + 2].second += lazy[v].second;
                }
            push(v * 2 + 1, tl, (tl + tr) / 2 , deg-1); 
            push(v * 2 + 2, (tl + tr) / 2 + 1, tr , deg-1);
        }
        lazy[v] = no_operation;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    
    void build(vector<int> &a){
        build(a,0,0,sz-1);
    }

    node query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return merge(left, right);
    }
    
    node query(int l,int r){
        return query(0,0,sz-1,l,r);
    }
    // set [l,r] to x
    void update(int v, int tl, int tr, int l, int r, int sum) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
             lazy[v].first += sum;
             lazy[v].second++;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), sum);
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, sum + (max(l, tm + 1) - l) );
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    
    void update(int l,int r){
         update(0,0,sz-1,l,r,0);
    }
};

vector<int> my_solution(const TestCase& tc) {
    int n = tc.n , q = tc.q;
    SegmentTree st(n);
    vector<int>v(n);
    st.build(v);
    vector<int> ret;
    for(int i = 0 ; i < q ; i++){
        if(tc.qu[i][0] == 1){
            st.update(tc.qu[i][1]-1,tc.qu[i][2]-1);
        }else{
            ret.push_back(st.query(tc.qu[i][1]-1,tc.qu[i][2]-1).val);
        }
    }
    return ret;
}

vector<int> correct_solution(const TestCase& tc) {
    int n = tc.n ,q = tc.q;
    vector<int> v(n);
    vector<int>ret;
    for(int i  =0 ;i  < q ; i++){
         if(tc.qu[i][0] == 1){
            int inc = 1;
            int l = tc.qu[i][1]-1; int r = tc.qu[i][2]-1;
            for(int x = l ; x <= r ; x++,inc++) v[x]+=inc;
        }else{
            int sum = 0;
            int l = tc.qu[i][1]-1; int r = tc.qu[i][2]-1;
            for(int x = l ; x <= r ; x++) sum+=v[x];
            ret.push_back(sum);
        }
    }
    return ret;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    const int T = 1000;
    for (int t = 1; t <= T; ++t) {
        TestCase tc = generate_input();
        auto res1 = my_solution(tc);
        auto res2 = correct_solution(tc);
        for(int i = 0 ; i < res1.size() ; i++){
            if(res1[i] != res2[i]){
                cout << "Test " << t << " failed.\n";
                cout << "Input:\n";
                cout<<tc.n<<" "<<tc.q<<"\n";
                for (int x : tc.a) cout << x << " ";
                cout<<"\n";
                for(auto it : tc.qu) cout<<it[0]<<" "<<it[1]<<" "<<it[2]<<'\n';
                cout << "\nMy output: ";
                for(auto it : res1) cout<<it<<" ";
                cout<<"\n";
                cout<<"\nExpected: ";
                for(auto it : res2)  cout<< it <<" ";
                cout << "\n";
                return 0;
            }
        }
    }
    cout << "All tests passed.\n";
    return 0;
}