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

    const int N = 505;
    const int M = 2005;
    int dp[N][M];
    void solve(int test_case) {
        int n; cin>>n;
        vi v(n); cin>>v;
        f(i,0,n)f(j,0,M) dp[i][j] = N;
        function<int(int,int)> rec = [&](int i,int val)->int{
            if(v[i] == val) return i;
            if(v[i] > val) return -1;
            int &ret = dp[i][val];
            if(ret != N) return ret;
            int cur = v[i];
            int idx = i+1;
            while (cur != val && idx < n){
                idx = rec(idx,cur);
                if(idx == -1) return -1;
                cur++,idx++;
            }
            return ret = (cur == val ? idx - 1 : -1);
        };
        vi res(n+1,INT64_MAX);
        res[n-1] = 1;
        res[n] = 0;
        for(int i = n-2 ; i >= 0 ; i--){
            for(int val = 1 ; val <= 2000 ; val++){
                int ret = rec(i,val);
                if(ret != -1) res[i] = min(res[i] , 1 + res[ret+1]);
            }
        }
        cout<<res[0]<<ln;
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