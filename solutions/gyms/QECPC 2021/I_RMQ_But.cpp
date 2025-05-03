#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}


struct SegmentTree {
    struct node {
        int mx,mn;
    };
    
    int n;
    vector<node> tree;
    vii lazy;
    node neutral = { INT_MIN , INT_MAX  };
    vi no_operation = {0,1};

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
        lazy = vii(2 * n , vi(2));
        f(i,0,2*n){
            lazy[i][0] = 0;
            lazy[i][1] = 1;
        }
    }

    node merge(const node &a, const node &b) {
        if(b.mn == INT_MAX) return a;
        if(a.mn == INT_MAX) return b;
        return { max({a.mx,b.mx,a.mn,b.mn}) , min({a.mn,b.mn,a.mx,b.mx} ) };
    }

    void push(int v, int tl, int tr , int deg = 1) {
        if(deg == 0) return;
        tree[v].mx += lazy[v][0];
        tree[v].mn += lazy[v][0];
        tree[v].mx *= lazy[v][1];
        tree[v].mn *= lazy[v][1];
        if(tree[v].mn > tree[v].mx) swap(tree[v].mn,tree[v].mx);

        if (tl != tr) {
        
                lazy[v * 2 + 1][0] += lazy[v][0];
                lazy[v * 2 + 2][0] += lazy[v][0];
                lazy[v * 2 + 1][1] *= lazy[v][1];
                lazy[v * 2 + 2][1] *= lazy[v][1];
         
            push(v * 2 + 1, tl, (tl + tr) / 2, deg-1); 
            push(v * 2 + 2, (tl + tr) / 2 + 1, tr , deg-1);
        }
        
    //    cout<<tl<<" "<<tr<<" "<<tree[v].mx<<ln;

        lazy[v][0] = 0;
        lazy[v][1] = 1;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) {
                tree[v] = { a[tl] , tl } ;
            }
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
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

    void update(int v, int tl, int tr, int l, int r, int addend ,int type) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
            if(type) lazy[v][0] += addend;
            else lazy[v][1] *= addend;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), addend , type );
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, addend , type );
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
};

void solve(int test_case){
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    SegmentTree st(n);
  //  cout<< st.query(0,0,n-1,0,0).mx<<ln;
    st.build(v,0,0,n-1);
    while(q--){
        int op,l,r; cin>>op>>l>>r; l--,r--;
        if(op == 1){
            int mx = st.query(0,0,n-1,l,r).mx;
            cout<<"mx "<<mx<<ln;
            st.update(0,0,n-1,l,r,-mx,1);
            st.update(0,0,n-1,l,r,-1,0);
             for(int i = 0 ; i < n ; i++){
                 cout<<i<<" "<<st.query(0,0,n-1,i,i).mx<<ln;
             }
            cout<<" -- "<<st.query(0,0,n-1,0,n-1).mx<<ln;
        }
        else{
            auto res = st.query(0,0,n-1,l,r);
            cout<<res.mx<<ln;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}