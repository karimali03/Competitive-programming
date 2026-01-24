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
    int n; cin>>n;
    vector<string>v(n); 
    f(i,0,n) cin>>v;
    sort(all(v),[](string &a,string &b){
        int sa = a.size() , sb = b.size();
        if(sa == sb){
            for(int i = 0;i < sa ; i++){
                if(a[i] != b[i]) return a[i] < b[i];
            }
            return true;
        }
        return sa < sb;
    });
    auto calc = [](string a,string b){
        int res = 0;
        reverse(all(a)); reverse(all(b));
        int sa = a.size() , sb = b.size();
        for(int i = 0;i < max(sa,sb) ; i++){
            int da = i >= sa ? 0 : a[i]-'0';
            int db = i >= sb ? 0 : b[i]-'0';
            res = res*10 + (da+db)%10;
        }
        return res;
    };
    cout<<calc(v[0],v[1])<<" "<<calc(v[n-2],v[n-1])<<ln;
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