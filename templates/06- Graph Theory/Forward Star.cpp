#define loop(u,e,v) for (int e = head[u], v; ~e && (v = to[e], 1); e = nxt[e])
const int N = 1000005;
const int M = 2000005;
int head[N],to[M],nxt[M],wt[M],ne;
void init(int n){
    ne = 0;
    memset(head,-1,n*sizeof(head[0]));
}
void add(int u,int v,int w = 0){
    to[ne] = v;
    nxt[ne] = head[u];
    wt[ne] = w;
    head[u] = ne++;
}
// Traverse neighbors of u
for(int e = head[u] ; ~e ; e = nxt[e]){
    int v = to[e];
    int w = wt[e];
}

// full struct
const int E = 1e6 + 5;
#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])
 
class ADJ {
   public:
    int head[E], to[E], nxt[E], n, edgcnt = 0;
    ll cst[E];
 
    void addEdge(int a, int b, int c = 0) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cst[edgcnt] = c;
        edgcnt++;
    }
 
    void addBiEdge(int a, int b, int c = 0) {
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj, nadj;
