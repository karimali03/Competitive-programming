// color 1 for left and 2 for right
// bipatie can have cycles with even length but not odd length
// if we can color the graph with 2 colors then it's bipartie
int vis[N]{};
int l,r;
bool vld;
void bipartie(int x,int color){
        vis[x] = color;
        int tag = color^3;
        if(color == 1) l++;
        else r++;
        loop(x,e,v){
            if(!vis[v])  bipartie(v,tag);
            else if(vis[v] != tag) vld = false;
        }
}
