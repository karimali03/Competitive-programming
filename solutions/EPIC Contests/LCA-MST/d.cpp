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


struct dsu {
    vector<int> size, par;
    int cc;

    dsu(int n) : cc(n), size(n + 1, 1), par(n + 1) {
        for (int i = 0; i <= n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        par[x] = y;
        size[y] += size[x];
        cc--;
        return true;
    }

};


struct edge {
	int from, to, w;

	edge(int from = -1 , int to = -1, int w = -1) :
			from(from), to(to), w(w) {
	}

	bool operator <(const edge &e) const {
		return w < e.w;
	}
};

int MST_Kruskal(vector<edge> &edgeList, int n) { // O(E logV)
	dsu uf(n);
	vector<edge> edges;	
	int mstCost = 0;

	sort(edgeList.begin(), edgeList.end());

	for(auto& e : edgeList) {
		if (uf.merge(e.from, e.to)) {
			// If added, then part of tree
			mstCost += e.w;
			edges.push_back(e);
		}
	}
	// if size of edges != n-1, then no full MST
	return mstCost;
}

void solve(int test_case) {
    int n,m; cin>>n>>m;
    vi v(n); cin>>v;
    int mni = 0;
    for(int i = 1 ; i < n; i++){
        if(v[mni] > v[i]) mni = i;
    }
    vector<edge> edg;
    for(int i = 0;i < n ; i++){
        if(i == mni) continue;
        edg.push_back({mni,i,v[mni]+v[i]});
    }
    for(int i =0;i < m ;i++){
        int x,y,w; cin>>x>>y>>w; x--,y--;
        edg.push_back({x,y,w});
    }
    int res = MST_Kruskal(edg,n);
    cout<<res<<ln;
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