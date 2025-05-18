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
	int from, to, w ;

	edge(int from = -1 , int to = -1, int w = -1) :
			from(from), to(to), w(w)  {
	}

	bool operator <(const edge &e) const {
		return w < e.w;
	}
};

int MST_Kruskal(vector<edge> &edgeList, int n , int idx) { // O(E logV)
	dsu uf(n);
	int mn = INT32_MAX;
    int mx = INT32_MIN;
	

	for(int i = idx  ;i  < edgeList.size() ; i++){
        auto e = edgeList[i];
		if (uf.merge(e.from, e.to)) {
			mn = min(mn , e.w);
            mx = max(mx , e.w);
		}
        if(uf.cc == 1) break;
	}
  
	if(uf.cc != 1) return INT32_MAX;
	return mx-mn;
}


void solve(int test_case) {
    int n,m; cin>>n>>m;
    vector<edge>v(m);
    f(i,0,m){
        int x,y,w; cin>>x>>y>>w;
        v[i] = edge(x,y,w);
    }
    sort(all(v));
    int mn = INT32_MAX;
    for(int i = 0 ; i < m ; i++){
        mn = min(mn , MST_Kruskal(v,n,i));
    }
    if(mn == INT32_MAX) NO;
    else {
        YES;
        cout<<mn<<ln;
    }
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