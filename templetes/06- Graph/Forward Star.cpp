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
