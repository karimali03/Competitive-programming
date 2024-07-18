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


struct segment_tree
{
    private:
        int size;


        vector<int> lazy;
        int NO_OPERATION = LLONG_MAX;
       
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
      
             lazy = vector<int>( size<<1 , NO_OPERATION );
        }
 
        void add(int l,int r , int v){
            _add(l,r,v,0,0,size);
        }
      

        int get(int i){
            return _get(i,0,0,size); 
        }

   
};
 


signed main() {
 
    return 0;
}