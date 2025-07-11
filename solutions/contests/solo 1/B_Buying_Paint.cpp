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

    #ifndef ONLINE_JUDGE
    #define debug(x) cerr << #x << " "; _print(x); cerr << endl;
    #else
    #define debug(x)
    #endif

    void _print(ll t) {cerr << t;}
    void _print(string t) {cerr << t;}
    void _print(char t) {cerr << t;}
    void _print(ld t) {cerr << t;}
    void _print(double t) {cerr << t;}
    void _print(ull t) {cerr << t;}

    template <class T, class V> void _print(pair <T, V> p);
    template <class T> void _print(vector <T> v);
    template <class T> void _print(set <T> v);
    template <class T> void _print(multiset <T> v);
    template <class T, class V> void _print(map <T, V> v);

    template <class T, class V> void _print(pair <T, V> p) {
        cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
    }
    template <class T> void _print(vector <T> v) {
        cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
    }
    template <class T> void _print(set <T> v) {
        cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
    }
    template <class T> void _print(multiset <T> v) {
        cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
    }
    template <class T, class V> void _print(map <T, V> v) {
        cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
    }

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

    const int N = 1005;
    int v[N][N]{};
    int di[] {0,1,0,-1};
    int dj[] {1,0,-1,0};
    int n;



int maxSubarraySum(const vector<int>& arr) {
    int max_sum = LLONG_MIN, curr_sum = 0;
    for (int x : arr) {
        curr_sum = max(x, curr_sum + x);
        max_sum = max(max_sum, curr_sum);
    }
    return max_sum;
}

    bool valid(int i,int j){
        return i>=0 && j>=0 && i<n && j<n;
    }
    int calc(int i,int j,int d){
        vii vis(n,vi(n));
        vi ret;
        int cnt = n*n;
     
        while(true){
            ret.push_back(v[i][j]);
          
            vis[i][j] = 1;
            cnt--;
            if(!cnt) break;
            while(!valid(i+di[d],j+dj[d]) || vis[i+di[d]][j+dj[d]]){
                d = (d+1)%4;
            }
            i+=di[d]; j+=dj[d];
        }
    
        return max(0ll ,maxSubarraySum(ret));
    }
    void solve(int test_case) {
        cin>>n;   
        f(i,0,n) f(j,0,n) cin>>v[i][j];
        vector<pair<int,int>> pr = {{0,0},{n-1,n-1},{0,n-1},{n-1,0}};
        int mx = 0;
        for(auto it  : pr){
            for(int i = 0 ; i < 4 ; i++){
                mx = max(mx , calc(it.first,it.second,i));
            }
        }
        cout<<mx<<ln;
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