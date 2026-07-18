/*
   sack on tree N log N * u, where u is the time taken to update the global data structure.
   used to answer queries on subtrees of a tree.
*/
const int N = 200005;
int sz[N] , big[N];
vector<int>g[N];
int color[N];
// Global data structure (e.g., frequency array, max variables)
int freq[N]{}; 
ll sum[N]{};
int mx = 0;
// answer
ll ans[N];
// preprocess the tree to compute sizes and identify big children 
void pre(int x,int p){
    sz[x] = 1;
    big[x] = -1;
    for(auto &y : g[x]) if(y != p){
        pre(y,x);
        sz[x] += sz[y];
        if( big[x] == -1 || sz[y] > sz[big[x]]) big[x] = y;
    }
}

void upd(int x,int d){
    int cl = color[x];
    if(freq[cl] + d > mx) mx++;
    else if(freq[cl] == mx && sum[mx] == cl) mx--;

    sum[freq[cl]] -= cl;
    freq[cl] += d;
    sum[freq[cl]] += cl;
}

// add or remove the contribution of a subtree rooted at 'x' to the global data structure
void add(int x,int p,int d){
    upd(x,d);
    for(auto &it : g[x]) if(it != p){
        add(it,x,d);
    }
}

void sack(int x,int p,int keep){
    // add and remove light nodes
    for(auto &it : g[x]) if(it != p && big[x] != it) sack(it,x,0);
    // add big child
    if(~big[x]) sack(big[x],x,1);
    // add myself
    upd(x,1);
    // add light nodes
    for(auto &it : g[x]) if(it != p && big[x] != it) add(it,x,1);
    // answer queries
    ans[x] = sum[mx];
    // remove if required
    if(!keep){
        add(x,p,-1);
        /* * HARD RESET:
         * Because add(..., -1) destroyed the entire subtree, the cnt array 
         * is exactly how we found it (empty). We can safely reset our global 
         * trackers to 0 without recalculating anything.
         * ex : mx = 0 , mn = 0
         */
    } 
}
