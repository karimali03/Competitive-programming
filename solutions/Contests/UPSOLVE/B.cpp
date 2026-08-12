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
struct Manacher {
    int n;
    vector<int> s;
    vector<int> d1, d2;
    
    Manacher(vector<int> _s) : s(_s) {
        n = s.size();
        d1.resize(n);
        d2.resize(n);
        build();
    }
    
    void build() {
        // odd: [i-d1[i]+1 ... i+d1[i]-1]
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r ? 1 : min(d1[l+r-i], r-i+1));
            
            while (i-k >= 0 && i+k < n && s[i-k] == s[i+k])
            k++;
            
            d1[i] = k--;
            
            if (i+k > r) {
                l = i-k;
                r = i+k;
            }
        }
        
        // even: [i-d2[i] ... i+d2[i]-1]
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r ? 0 : min(d2[l+r-i+1], r-i+1));

            while (i-k-1 >= 0 && i+k < n && s[i-k-1] == s[i+k])
                k++;
                
            d2[i] = k--;

            if (i+k > r) {
                l = i-k-1;
                r = i+k;
            }
        }
    }
    
    // 0-indexed inclusive [l, r]
    bool is_pal(int l, int r) {
        int len = r-l+1;

        if (len & 1) {
            int mid = (l+r)/2;
            return d1[mid] >= len/2 + 1;
        } else {
            int mid = (l+r+1)/2;
            return d2[mid] >= len/2;
        }
    }
    
    vector<int> cnt_start(){
        vi cnt(n+1);

        for(int i = 0; i < n; i++){
            cnt[i-d1[i]+1]++; cnt[i+1]--;
            cnt[i-d2[i]]++;   cnt[i]--;
        }
        for(int i = 1; i < n; i++)
            cnt[i] += cnt[i-1];
        cnt.pop_back();
        return cnt;
    }
    
    
    vector<int> cnt_end(){
        vi cnt(n+1);

        for(int i = 0; i < n; i++){
            cnt[i]++;  cnt[i+d1[i]]--;
            cnt[i]++;  cnt[i+d2[i]]--;
        }
        for(int i = 1; i < n; i++)
            cnt[i] += cnt[i-1];
        cnt.pop_back();
        return cnt;
    }
};
void solve(int test_case) {
    string a,b; cin>>a>>b;
    int n = a.size();
    int i = 0;
    int L  = 0;
    while(i < n && (a[i] == b[n-i-1]) && (b[i] == a[n-i-1])) i++,L++;
    int res = L;
    vi X(n);
    for(int i = 0;i < n; i++){
        X[i] = (a[i]-'a'+1) * 26 + (b[i]-'a'+1);
    }
    Manacher man(X);
    auto st = man.cnt_start();
    auto en = man.cnt_end();
    // macher (Ai,Bi)
  //  cout<<st<<ln;
   // cout<<en<<ln;
    for(int i = 1 ; i < min(L+1,n) ; i++){
        res += st[i];
    }
    for(int i = n-2 ; i >= max(n-L-1,0ll) ; i--){
        res += en[i];
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