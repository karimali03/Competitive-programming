#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define int long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>


struct item{
    int mn;
    item(int mn = 0 ):mn(mn){}
};

struct segment_tree
{
    private:
        int size;

        vector<item> seg;
        vector<int> lazy;
        int NO_OPERATION = LLONG_MAX;
        
        item neutral = {  0  };
 
        item merge(item &x , item &y){
            return item{ min(x.mn , y.mn)  };
        }
 
         item single(int v){
            return item{v};
        }

        int operation(int a, int b){
            if(b == NO_OPERATION) return a;
            return b;
        }

        void propagate(int idx , int lx , int rx){
            if(rx - lx == 1) return;
            lazy[2 * idx + 1] = operation( lazy[2 * idx + 1] , lazy[idx] );
            lazy[2 * idx + 2] = operation( lazy[2 * idx + 2] , lazy[idx] );
            lazy[idx] = NO_OPERATION;
        }

 
        void _set(int i,int v,int idx,int lx,int rx){
            if(rx - lx == 1){
                seg[idx] = single(v);
                return;
            }
            int m = (lx + rx) / 2;
            if(i < m) _set(i , v , idx * 2 + 1 , lx , m );
            else  _set(i , v , idx * 2 + 2 , m  , rx);
            
            seg[idx] = merge( seg[2 * idx + 1] , seg[2 * idx + 2] );
            
        }
 
 
        int _query(int l , int r , int p , int idx , int lx , int rx){
           
            if(lx >= r || rx <= l || seg[idx].mn > p ) return 0;
            
            if(rx - lx == 1) {
                set(lx,INT_MAX);
                return 1;
            }
                
            int m = (lx + rx) / 2;
            int left = _query(l , r , p , idx * 2 + 1 , lx , m);
            int right = _query(l , r , p , idx * 2 + 2 , m , rx);
            return left + right;

        }

        void _add(int l , int r, int v , int idx , int lx , int rx){
            propagate(idx,lx,rx);
            if(lx >= r || rx <= l) return;
            if(lx >= l && rx <= r){
                lazy[idx] = operation( lazy[idx] , v); 
                return;
            }
            int m = (lx + rx) / 2;
            _add(l , r , v , idx * 2 + 1 , lx , m);
            _add(l , r , v , idx * 2 + 2 , m , rx);
        }

        int _get(int i , int idx , int lx, int rx){
            propagate(idx,lx,rx);
            if(rx - lx == 1) return lazy[idx];
            int m = (lx + rx) / 2;
            int res;
            if(i < m) res = _get(i , idx * 2 + 1 , lx , m);
            else res = _get(i , idx * 2 + 2 , m , rx);
            return res ;
        }
    
    public:
          segment_tree(int n){
            size = 1;
            while (size < n)
            {
                size<<=1;
            }
             seg = vector<item>( size<<1 , neutral );
             lazy = vector<int>( size<<1 , 0 );
        }
 
        void add(int l,int r , int v){
            _add(l,r,v,0,0,size);
        }
        void set(int i , int v){
            assert(i >=0 && i < size);
            _set(i,v,0,0,size);
        }

        int query(int l , int r , int p){
            return _query(l,r, p , 0,0,size);

        }

        int get(int i){
            return _get(i,0,0,size); 
        }

        
 
     
};
 


signed main() {
 
    return 0;
}