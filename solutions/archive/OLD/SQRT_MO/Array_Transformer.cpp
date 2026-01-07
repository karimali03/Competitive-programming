#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define vec vector
#define vi vector<int>
#define f(i, a, b) for(int i=a;i<b;i++)
#define int long long

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}

void solve(int test_case) {
    int n, m, u;
    cin >> n >> m >> u;
    vi v(n), sq(n);
    f(i, 0, n) cin >> v[i];
    sq = v;
    
    int SQ = sqrt(n) + 1;
    for(int i = 0; i < SQ; i++) {
        int l = SQ * i;
        int r = min(n, SQ * i + SQ);
        if(l >= n) break;
        sort(sq.begin() + l, sq.begin() + r);
    }
    
    while(m--) {
        int l, r, vx, idx;
        cin >> l >> r >> vx >> idx;
        if(l > r) swap(l, r);
        l--; r--; idx--;
        
        int k = 0;
        for(int i = (l/SQ) + 1; i < r/SQ; i++) {
            int block_end = min(n, i*SQ + SQ);
            k += lower_bound(sq.begin() + i*SQ, sq.begin() + block_end, vx)
                - (sq.begin() + i*SQ);
        }
        
        int left_end = min(r + 1, ((l/SQ)*SQ + SQ));
        k += lower_bound(sq.begin() + l, sq.begin() + min(n, left_end), vx)
            - (sq.begin() + l);
        
        if(l/SQ != r/SQ) {
            int right_start = (r/SQ)*SQ;
            k += lower_bound(sq.begin() + right_start, sq.begin() + min(n, r + 1), vx)
                - (sq.begin() + right_start);
        }
        
        int range = r - l + 1;
        int val = (range > 0) ? (u * k) / range : 0;  // Prevent division by zero
        
        v[idx] = val;
        int block_start = (idx/SQ) * SQ;
        int block_end = min(n, block_start + SQ);
        for(int i = block_start; i < block_end; i++) {
            sq[i] = v[i];
        }
        sort(sq.begin() + block_start, sq.begin() + block_end);
    }
    
    f(i, 0, n) cout << v[i] << ln;
}