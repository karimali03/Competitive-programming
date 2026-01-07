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
Time Complexity: O(n^3)
  - You need **all-pairs shortest paths**
  - Graph is dense (many edges: m ≈ n^2)
  - Graph size is small (n ≤ 500)
  - Graph has negative weights (but no negative cycles)
  - You want to **detect negative cycles** (check dist[i][i] < 0)
-> DON'T use Floyd-Warshall when:
  - Graph is **sparse** (m ≪ n^2): use Dijkstra or Bellman-Ford
Negative cycle detection:  for (int i = 0; i < n; ++i)  if (dist[i][i] < 0) → Negative cycle exists

*/
const int N = 505;
const int INF = 1e16;
int v[N][N], path[N][N];
int n;
void flyod() {
    f(i, 0, n) f(j, 0, n) path[i][j] = -1;
    f(i, 0, n) v[i][i] = 0;

    f(i,0,n) f(j,0,n){
        int x; cin>>x;
        if(x == 100000) v[i][j] = INF;
        else v[i][j] = x;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if(v[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if(v[k][j] == INF) continue;
                int relax = v[i][k] + v[k][j];
                if (relax < v[i][j]) {
                    v[i][j] = relax;
                    path[i][j] = k;
                }
            }
        }
    }
}

void build_path(int from, int to, vector<int> &road) {
    cout<<from<<" "<<to<<" "<<path[from][to]<<endl;
    if (path[from][to] == -1) {
        road.push_back(from);
        if (from != to) road.push_back(to);
        return;
    }
    int mid = path[from][to];
    build_path(from, mid, road);
    road.pop_back();  
    build_path(mid, to, road);
}

void solve(int test_case) {
    cin>>n;
    for(int i = 0;i < n ; i++){
        for(int j = 0;j < n ; j++){
            path[i][j] = -1;
            int x; cin>>x;
            if(x == 100000) v[i][j] = INF;
            else v[i][j] = x,path[i][j]=i;
        }
    }
    for(int k = 0; k < n ; k++){
        for(int i = 0;i < n;  i++){
            if(v[i][k] == INF) continue;
            for(int j = 0;j < n ; j++){
                if(v[k][j] == INF) continue;
                int relax = max ( -INF , v[i][k] + v[k][j]);
                if(relax < v[i][j]){
                    v[i][j] = relax;
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    f(i,0,n) if(v[i][i] < 0){
        YES;
        vi ret;
        int cur = i;
        while(true){
            ret.push_back(cur);
            cur = path[i][cur];
            if(cur == i && ret.size() > 1){
                ret.push_back(i);
                break;
            }
            if((int)ret.size() > n * 2) break;
        }
        reverse(all(ret));
        cout<< ret.size() << ln;
        for(auto &it : ret) cout<<it+1<<" ";
        cout<<ln;
        return;
    }
    NO;
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