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

void solve(int test_case) {
    int n,k; cin>>n>>k;
    vi frq(n+1);
    for(int i = 0;i < n ; i++){
        int x; cin>>x;
        frq[x]++;
    }
    auto can = [&](int x) -> bool{
        vi freq = frq;
        int rem = n;
        int s = k + n + x * 2 - 1;
        int p = n;
        while(rem > 0){
            while(!freq[p]) p--;
            if(p <= s){
                freq[p]--; s--; rem--;
            }else{
                freq[p]--; freq[(p+1)/2] += 2; rem++; x--;
                if(x < 0) return false;
            }
        };
        return true;
    };
    int l = 0,r = n;
    int ans = 0;
    while(l<=r){
        int m = (l+r)/2;
        if(can(m)){
            ans = m; r = m-1;
        }else{
            l = m+1;
        }
    }
    cout<<ans*2+n<<ln;
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