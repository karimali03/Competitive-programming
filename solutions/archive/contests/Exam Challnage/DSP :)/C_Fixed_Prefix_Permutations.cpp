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


struct Trie {
    private:
        
        Trie* child[10]; 
        bool isLeaf;
        char base; // '0' or 'a' or 'A'
    
    public:
        Trie(char baseChar = '0') : isLeaf(false), base(baseChar) {
            memset(child,0,sizeof(child));
        }
    
        void insert(vector<int> &v, int idx = 0) {
            Trie* ptr = this;
            int n = v.size();
            for (int i = idx; i < n; i++) {
                int index = v[i];
    
                if (!ptr->child[index]) {
                    ptr->child[index] = new Trie(base);
                }
                ptr = ptr->child[index];
                if (i == n - 1) ptr->isLeaf = true;
            }
        }
    
       
        int prefix_exist(vector<int>& v) {
            int n = v.size();
            Trie* ptr = this;
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                int index = v[i];
                if (!ptr->child[index]) return cnt;
                cnt++;
                ptr = ptr->child[index];
            }
            return cnt;
        }
};
    




void solve(int test_case) {
    int n,m; cin>>n>>m;
    Trie st;
    vii v(n,vi(m));
    f(i,0,n){
        f(j,0,m) cin>>v[i][j],v[i][j]--;
    }
    f(i,0,n){
        vi idx(m);
        f(j,0,m) idx[v[i][j]] = j;
        st.insert(idx);
    }
    f(i,0,n){
        int res = st.prefix_exist(v[i]);
        cout<<res<<" ";
    }
    cout<<ln;
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