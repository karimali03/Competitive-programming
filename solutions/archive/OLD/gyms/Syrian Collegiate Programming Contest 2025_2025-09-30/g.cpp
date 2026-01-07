#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define vi vector<int>
#define vii vector<vi>
#define f(i,a,b) for(int i=a;i<b;i++)
#define int long long 


const int INF = 1e9;
int dx[] = {-1,1,0,0}; // UDLR
int dy[] = {0,0,-1,1};

void solve(){
    int n,m,k; cin>>n>>m>>k;

    vector<vi> to(2, vi(4));
    to[0] = {3,2,1,0}; // '/'
    to[1] = {2,3,0,1}; // '\'

    pair<int,int> st,en;
    int ds,de;
    char c;
    cin>>st.first>>st.second; st.first--, st.second--;
    cin>>c;
    ds = (c=='U'?0:(c=='D'?1:(c=='L'?2:3)));
    cin>>en.first>>en.second; cin>>c; en.first--, en.second--;
    de = (c=='U'?0:(c=='D'?1:(c=='L'?2:3)));

    vii grid(n,vi(m,3));
    f(i,0,n) f(j,0,m){
        cin>>c;
        if(c=='\\') grid[i][j]=1;
        else if(c=='/') grid[i][j]=0;
        else grid[i][j]=3;
    }

    // 0-1 BFS
    vii d(n*m, vi(4,INF));
    d[st.first*m+st.second][ds] = 0;
    deque<pair<int,int>> q;
    q.push_front({st.first*m+st.second,ds});
    while (!q.empty()) {
        auto [cor,dr] = q.front(); q.pop_front();
        int cur = d[cor][dr];
        if(cur > k) continue;
        int x = cor/m , y = cor%m;
     //   cout<<q.size()<<endl;
        cout<<x<<" "<<y<<" "<<dr<<" "<<cur<<" "<<grid[x][y]<<" "<<endl;
        if( (x == en.first)  && (y == en.second) ){
            if((grid[x][y] == 3 && de == dr)) d[x*m+y][de] = min(d[x*m+y][de] , cur);
            else if(grid[x][y] != 3 && de == to[grid[x][y]][dr]) d[x*m+y][de] = min(d[x*m+y][de] , cur);
            else if(grid[x][y] != 3 && de == to[1-grid[x][y]][dr])  d[x*m+y][de] = min(d[x*m+y][de],cur+1);
            continue;
        }
        if(grid[x][y] == 3){
            int nx = x + dx[dr];
            int ny = y + dy[dr];
            if(nx >= 0 && ny >= 0 && nx < n && ny < m){
                d[nx*m+ny][dr] = min(d[nx*m+ny][dr],cur);
                q.push_front({nx*m+ny,dr});
            }
            continue;
        }
        int nx = x + dx[to[grid[x][y]][dr]];
        int ny = y + dy[to[grid[x][y]][dr]];
        if(nx >=0 && ny >= 0 && nx < n && ny < m ){
             d[nx*m+ny][to[grid[x][y]][dr]] = min(  d[nx*m+ny][to[grid[x][y]][dr]],cur);
             q.push_front({nx*m+ny,to[grid[x][y]][dr]});
        }
        nx = x + dx[to[1-grid[x][y]][dr]];
        ny = y + dy[to[1-grid[x][y]][dr]];
        if(nx >=0 && ny >= 0 && nx < n && ny < m ){
             d[nx*m+ny][to[1-grid[x][y]][dr]] = min( d[nx*m+ny][to[1-grid[x][y]][dr]],cur+1);
             q.push_back({nx*m+ny,to[1-grid[x][y]][dr]});
        }
    }
  //  cout<<en.first*m+en.second<<" "<<de<<endl;
    if(d[en.first*m+en.second][de] <= k) cout<<d[en.first*m+en.second][de]<<ln;
    else cout<<-1<<ln;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    while(t--) solve();
}
