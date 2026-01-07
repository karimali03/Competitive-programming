#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("unroll-loops")

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

const int N = 105;
int v[N][N];

const int OO =  1e9;
 
struct edge {
	int x,y, w;
 
	edge(int x = 0,int y = 0,int w = 0) :
			x(x),y(y), w(w) {
	}
 
	bool operator <(const edge &e) const {
		return w > e.w;
	}
};
 
 
void solve(int test_case) {
    int n,m; cin>>n>>m;
    f(i,0,n) f(j,0,m){
        char c; cin>>c;
        v[i][j] = c-'0';
    }
    int a,b,c,d; cin>>a>>b>>c>>d; 
    int k; cin>>k;
    vector<string>str(k);
    f(i,0,k) cin>>str[i];
    map<char,pair<int,int>>mp;
    map<pair<pair<int,int>,int>,pair<int,pair<int,int>>>vis;
    mp['U'] = {-1,0}; mp['D'] = {1,0}; mp['L'] = {0,-1}; mp['R'] = {0,1};
    vii dist(n,vi(m,OO));
	priority_queue<edge> q;	
	q.push(edge(a,b,0));
  
    while(!q.empty()){
        edge mn = q.top(); q.pop();
		int x = mn.x , y = mn.y;
		if(dist[x][y] != OO) continue;
		dist[x][y] = mn.w;
        if(x == c && y == d){
            cout<<dist[x][y]<<ln;
            return;
        }
        for(int l = 0 ; l < k ; l++){
                    int sz = str[l].size();
                    int cnt = 0;
                    pair<int,int> idx = {x,y};
                    for(int ptr = 0 ; ptr < sz ; ptr++){
                        auto sh = mp[str[l][ptr]]; 
                        pair<int,int> ind = {idx.first+sh.first,idx.second+sh.second};
                        if(ind.first < 0 || ind.first >= n || ind.second < 0 || ind.second >= m) continue;
                        if(v[ind.first][ind.second] == 1) continue;
                        idx = ind;
                        cnt++;
                    }
                    if(dist[idx.first][idx.second] == OO)
                    q.push({ idx.first , idx.second , cnt + dist[x][y] });
        }
    }
    cout<<-1<<ln;


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