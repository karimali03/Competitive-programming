#include <iostream>
#include <cassert>
using namespace std;
#include <vector>
#include <climits>
#define int long long

struct segment_tree
{
    private:
        int size;
        vector<int> seg;
        int neutral = 1e10;
 
        int merge(int a , int b){
            return min ( a , b );
        }
 
        void _set(int i,int v,int idx,int lx,int rx){
            if(rx - lx == 1){
                seg[idx] = v;
                return;
            }
            int m = (lx + rx) / 2;
            if(i < m) _set(i,v,idx * 2 + 1 , lx , m );
            else  _set(i , v , idx * 2 + 2 , m  , rx);
            
            seg[idx] = merge( seg[2 * idx + 1] , seg[2 * idx + 2] );
 
        }
 
        int _sum(int idx , int l, int r, int lx , int rx){
            if(l >= rx || r <= lx) return neutral;
            if(lx >= l  && rx <= r) return seg[idx];
            int m = (lx+rx)/2;
            int left = _sum(idx * 2 + 1 , l , r , lx , m);
            int right = _sum(idx * 2 + 2 , l , r , m , rx);
 
            return merge ( left , right ) ;
        }
 
    public:
          segment_tree(int n){
            size = 1;
            while (size < n)
            {
                size<<=1;
            }
             seg = vector<int>( size<<1 ,neutral);
        }
 
        void set(int i , int v){
            assert(i >=0 && i < size);
            _set(i,v,0,0,size);
        }
        int sum(int l , int r){
            assert(l >=0 && l <= size && r >= 0 && r <= size);
            return _sum(0 , l , r , 0 , size);
        }
 
};


signed main(){
    int n,m; cin>>n>>m;
    segment_tree seg(n);
    for(int i = 0 ; i < n ;i++){
        int x; cin>>x;
        seg.set(i,x);
    }    
    while (m--)
    {
        int c; cin>>c;
        if(c == 1){
            int i,v; cin>>i>>v;
            seg.set(i,v);
        }
        else{
            int l,r; cin>>l>>r;
            cout<<seg.sum(l,r)<<"\n";
        }
    }
    
    return 0;
}