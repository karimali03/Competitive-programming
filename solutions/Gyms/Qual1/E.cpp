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



#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct SPT2D {
    int n, m;
    int log_n, log_m;
    
    // st[i][j][x][y] stores the maximum in a rectangle 
    // starting at (x, y) with height 2^i and width 2^j
    vector<vector<vector<vector<T>>>> st;

    // Constructor builds the table in O(N * M * log N * log M)
    SPT2D(const vector<vector<T>>& a) {
        n = a.size();
        m = a[0].size();
        log_n = __lg(n) + 1;
        log_m = __lg(m) + 1;

        st.assign(log_n, vector<vector<vector<T>>>(log_m, 
               vector<vector<T>>(n, vector<T>(m))));

        // 1. Base case: 1x1 rectangles
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                st[0][0][i][j] = a[i][j];
            }
        }

        // 2. Build 1-D Sparse Tables for each row: 1 x (2^j) rectangles
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < log_m; j++) {
                for (int y = 0; y + (1 << j) <= m; y++) {
                    st[0][j][i][y] = max(st[0][j - 1][i][y], 
                                         st[0][j - 1][i][y + (1 << (j - 1))]);
                }
            }
        }

        // 3. Build 2-D Sparse Table: (2^i) x (2^j) rectangles
        for (int i = 1; i < log_n; i++) {
            for (int j = 0; j < log_m; j++) {
                for (int x = 0; x + (1 << i) <= n; x++) {
                    for (int y = 0; y + (1 << j) <= m; y++) {
                        // Combine two halves vertically
                        st[i][j][x][y] = max(st[i - 1][j][x][y], 
                                             st[i - 1][j][x + (1 << (i - 1))][y]);
                    }
                }
            }
        }
    }

    // Query max in rectangle from (x1, y1) to (x2, y2) in strictly O(1)
    T query(int x1, int y1, int x2, int y2) {
        int kx = __lg(x2 - x1 + 1);
        int ky = __lg(y2 - y1 + 1);

        int len_x = 1 << kx;
        int len_y = 1 << ky;

        // Overlap four rectangles of size (2^kx) x (2^ky) 
        // to cover the exact queried area
        T max1 = st[kx][ky][x1][y1];
        T max2 = st[kx][ky][x2 - len_x + 1][y1];
        T max3 = st[kx][ky][x1][y2 - len_y + 1];
        T max4 = st[kx][ky][x2 - len_x + 1][y2 - len_y + 1];

        return max({max1, max2, max3, max4});
    }
};

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vii ret(n,vi(n,-1e9));
    for(int l = 0;l < n ; l++){
        int prv = v[l];
        ret[l][l] = prv;
        for(int r = l+1 ; r < n ; r++){
            int cur = (v[r]|prv) - (v[r]+prv);
            cur += (v[r]|prv);
            ret[l][r] = cur;
            prv = cur;
        }
    }
    SPT2D st(ret);
    int q; cin>>q;
    while(q--){
        int l,r; cin>>l>>r; l--,r--;
        cout<<st.query(l,l,r,r)<<ln;
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