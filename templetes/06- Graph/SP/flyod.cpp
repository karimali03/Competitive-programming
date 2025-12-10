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
#define ll long long
#define vec vector
#define f(i, a, b) for(int i = a; i < b; i++)

const int N = 505;
const int INF = 1e9;
int v[N][N];
int path[N][N]; // For recursive "Intermediate Node" reconstruction
int par[N][N];  // For iterative "Predecessor" reconstruction (Negative Cycles)
int n, m;

void flyod() {
    // 1. Initialize
    f(i, 0, n) {
        f(j, 0, n) {
            v[i][j] = INF;
            path[i][j] = -1;
            par[i][j] = -1; // -1 means no path
        }
        v[i][i] = 0;
        par[i][i] = -1; 
    }

    // 2. Read Input
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c; a--, b--;
        if (c < v[a][b]) {
            v[a][b] = v[b][a] = c;
            
            // Recursive setup
            path[a][b] = path[b][a] = -1; 
            
            // Iterative setup: Predecessor of b (coming from a) is a
            par[a][b] = a; 
            par[b][a] = b;
        }
    }

    // 3. Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if(v[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if(v[k][j] == INF) continue;
                
                int relax = v[i][k] + v[k][j];
                if (relax < v[i][j]) {
                    v[i][j] = relax;
                    
                    // Update Intermediate Node (for recursive build_path)
                    path[i][j] = k; 
                    
                    // Update Predecessor (for iterative neg_cyc)
                    // The node before 'j' on path i->...->k->j is the same 
                    // as the node before 'j' on path k->j.
                    par[i][j] = par[k][j]; 
                }
            }
        }
    }
}

// Recursive Path Reconstruction (Standard paths)
void build_path(int from, int to, vector<int> &road) {
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

// Iterative Negative Cycle Reconstruction
vector<int> neg_cyc(){
  for(int i = 0; i < n; i++){
        // If distance from i to i is negative, i is part of a negative cycle
        if(v[i][i] < 0){
           vector<int> ret;
           int cur = i;
           
           // We trace backwards: i <- pred <- pred ... <- i
           while(true){
              ret.push_back(cur);
              
              // Move to the predecessor of 'cur' on the path starting from 'i'
              cur = par[i][cur]; 
              
              // Validations to prevent infinite loops if par is broken
              if(cur == -1) return {}; // Should not happen if logic is correct
              
              // If we returned to start (i) and have a real path
              if(cur == i && ret.size() > 1){
                  ret.push_back(i); // Close the loop
                  break;
              }
              // Safety break
              if((int)ret.size() > 2 * n) break;
           }
           
           // Since we traced backwards, we reverse to get forward order
           reverse(ret.begin(), ret.end());
           return ret;
        }
  }
  return {};
}
