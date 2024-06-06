#include <iostream>
#include <cassert>
using namespace std;
#include <vector>
#include <climits>
#define int long long


typedef int item;

struct segment_tree
{
    private:
        int size;
        vector<item> seg;
 
 
        item neutral = 0;
 
        item merge(item a , item b){
            return a  + b;
        }
 
        item single(int v){
            return v;
        }

 
        void _set(int i,int v,int idx,int lx,int rx){
            if(rx - lx == 1){
                seg[idx] = v;
                return;
            }
            int m = (lx + rx) / 2;
            if(i < m) _set(i , v , idx * 2 + 1 , lx , m );
            else  _set(i , v , idx * 2 + 2 , m  , rx);
            
            seg[idx] = merge( seg[2 * idx + 1] , seg[2 * idx + 2] );
            
        }
 
 
        void _build(vector<int> & v , int idx , int lx , int rx){
            if(rx - lx == 1) {
                if(lx < (int)v.size()) seg[idx] = single(v[lx]);
                else seg[idx] = neutral;
                return;
            }
 
            int m = (lx + rx)/2;
            _build(v , idx * 2 + 1 , lx , m);
            _build(v , idx * 2 + 2 , m , rx);
 
            seg[idx] = merge(seg[idx * 2 + 1],seg[idx * 2 + 2]);
 
        }

        int _query(int l , int r , int idx , int lx , int rx){
         //   print("seg",l,r,lx,rx);
            if(lx >= r || l >= rx) return neutral;
            if(lx >= l && rx <= r) return seg[idx];
          //  print(l,r,idx,lx,rx,seg[idx]);
            int m = (lx + rx) / 2;
            int left = _query(l , r , 2 * idx + 1 , lx , m);
            int right = _query(l , r , 2 * idx + 2 , m , rx);
            return merge(left ,right);
        }
 
    
    public:
          segment_tree(int n){
            size = 1;
            while (size < n)
            {
                size<<=1;
            }
             seg = vector<item>( size<<1 );
        }
 
        void build(vector<int> & v){
            _build(v,0,0,size);
        }
 
        void set(int i , int v){
            assert(i >=0 && i < size);
            _set(i,v,0,0,size);
        }

        int query(int l , int r){
            return _query(l,r,0,0,size);
        }
 
     
};

signed main(){
    
    return 0;
}