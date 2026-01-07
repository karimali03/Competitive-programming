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

const int mod = 1e9+7;

int add(int a,int b){
    return (a%mod + b%mod)%mod;
}
int mul(int a,int b){
    return (a%mod*b%mod)%mod;
}

int fp(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = mul(res,a);
        a = mul(a,a);
        b/=2;
    }
    return res;
}

const int N = 100005;
int power[N];
void init(){
    for(int i = 1 ;i  < N ; i++){
        power[i] = fp(i,mod-2);
    }
}

struct Sqrt {
	int block_size;
	vector<int> nums , numsSorted;
    vector<int> suf;
    int n;
    pair<int,int> block_rng(int block){
        return {block * block_size , min( n , (block+1) * block_size)};
    }
	Sqrt(int sqrtn, vector<int> &arr) : block_size(sqrtn) {
		numsSorted = nums = arr;
        n = nums.size();
        suf = vi(n);
        for(int i = 0 ; i < (n + block_size - 1) / block_size ; i++){
            auto it = block_rng(i);
            sort(numsSorted.begin()+it.first,numsSorted.begin()+it.second);
            for(int x = it.second-1 ;  x >= it.first ; x--){
                suf[x] = power[numsSorted[x]];
                if(x+1 < it.second) suf[x] = mul(suf[x],suf[x+1]);
            }
        }
	}


	/** O(1) update to set nums[x] to v */
	void update(int x, int v) {
		nums[x] = v;
        auto it = block_rng(x/block_size);
        for(int i = it.first ; i < it.second ; i++) numsSorted[i] = nums[i];
        sort(numsSorted.begin()+it.first,numsSorted.begin()+it.second);
        for(int x = it.second-1 ;  x >= it.first ; x--){
                suf[x] = power[numsSorted[x]];
                if(x+1 < it.second) suf[x] = mul(suf[x],suf[x+1]);
        }
	}

	/** O(sqrt(n)) query for sum of [l, r] */
	long long query(int l, int r,int x) { 
        int res = 1;
        auto it = block_rng(l/block_size);
        for(int i = l ; i  < min(it.second , r+1) ; i++){
            res = mul(res , min(x,nums[i]));
            res = mul(res , power[nums[i]]);
        }
        if( l/block_size == r / block_size) return res;
        it = block_rng(r/block_size);
        for(int i = it.first ; i <= r ; i++){
             res = mul(res , min(x,nums[i]));
             res = mul(res , power[nums[i]]);
        }
        for(int i = l/block_size+1 ; i < r/block_size ; i++){
            it = block_rng(i);
            auto id = upper_bound(numsSorted.begin()+it.first , numsSorted.begin() + it.second, x) - numsSorted.begin();
            if(id != it.second){
                res = mul(res , fp(x,it.second-id));
                res = mul(res,suf[id]);
            }
        }
        return res;
     }
};

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    int sq = sqrt(n)+1;
    Sqrt st(sq,v);
    int q; cin>>q;
    while (q--)
    {
        int op; cin>>op;
        if(op == 1){
            int x,y; cin>>x>>y; x--;
            st.update(x,y);
        }else{
            int l,r,x; cin>>l>>r>>x; l--,r--;
            cout<<st.query(l,r,x)<<"\n";
        }
    }
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    init();
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}