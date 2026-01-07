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

/*
 Index-to-Block:
   - block_id = idx / block_size
 Block-to-Index:
   - block_start = block_id * block_size
   - block_end = min(n - 1, (block_id + 1) * block_size - 1)
*/
struct Sqrt {
	int block_size;
	vector<int> nums;
	vector<long long> blocks;
	int n,nb;
    pair<int,int> block_rng(int block){
            return {block * block_size , min( n , (block+1) * block_size)};
    }
     
	Sqrt(int sqrtn, vector<int> &arr) : block_size(sqrtn), blocks(sqrtn, 0) {
		nums = arr;
		n = nums.size();
        nb = ((n-1) / block_size) + 1;
		for (int i = 0; i < nums.size(); i++) { blocks[i / block_size] += nums[i]; }
	}

	/** O(1) update to set nums[x] to v */
	void update(int x, int v) {
		blocks[x / block_size] -= nums[x];
		nums[x] = v;
		blocks[x / block_size] += nums[x];
	}

	/** O(sqrt(n)) query for sum of [0, r) */
	long long query(int r) {
		long long res = 0;
		for (int i = 0; i < r / block_size; i++) { res += blocks[i]; }
		for (int i = (r / block_size) * block_size; i < r; i++) { res += nums[i]; }
		return res;
	}

	/** O(sqrt(n)) query for sum of [l, r) */
	long long query(int l, int r) { return query(r) - query(l - 1); }
};

void solve(int test_case) {
    int n,m,q; cin>>n>>m>>q;
    vii v(n,vi(m));
    vi cnt(m);
    for(int i = 0 ;i  < n ; i++){
        for(int j = 0 ; j < m ; j++){
            char c; cin>>c;
            v[i][j] = c-'0'; 
            cnt[j] += (c == '1');
        }
    }
    int sq = sqrt(m) + 1;
 
    Sqrt st(sq,cnt);
    while(q--){
        int x,y; cin>>x>>y; x--,y--;
        st.update(y, (v[x][y] ? -1 : 1));
        v[x][y] = 1 - v[x][y];
        if(st.query()) YES;
        else NO;
    }
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