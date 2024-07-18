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
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
 
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
     cout << endl;
}
 
template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}
 
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x: v) out << x << ' ';
    return out;
}
 

 

typedef int item;
struct segment_tree
{
    private:
        int size;
 
        vector<item> seg;
        item neutral = 0;


        item merge(item &x , item &y){
            return x + y;
        }
 
         item single(int v){
            return v;
        }
 



        vector<int> lazy;
        int NO_OPERATION = LLONG_MAX;
        
    
        int operation(int a, int b , int len){
                if(b == NO_OPERATION) return  a;
                if(a == NO_OPERATION) return  b;
                return  a + b * len;
        }
 
        void propagate(int idx , int lx , int rx){
            if(rx - lx == 1) return;
            int len = (rx - lx) / 2;
        
            lazy[2 * idx + 1] = operation( lazy[2 * idx + 1] , lazy[idx] , 1);
            seg[2 * idx + 1] = operation( seg[2 * idx + 1] , lazy[idx]  , len );
            lazy[2 * idx + 2] = operation( lazy[2 * idx + 2] , lazy[idx] , 1 );
            seg[2 * idx + 2] = operation( seg[2 * idx + 2] , lazy[idx] , len );
            lazy[idx] = NO_OPERATION;
        }
 

        int _query(int l , int r ,  int idx , int lx , int rx){

            propagate(idx , lx , rx);
            if(lx >= r || rx <= l ) return neutral;
            if(lx >= l && rx <= r) return seg[idx];
            int m = (lx + rx) / 2;
            int left = _query(l , r  , idx * 2 + 1 , lx , m);
            int right = _query(l , r , idx * 2 + 2 , m , rx);
            return merge ( left , right );

        }
 
        void _add(int l , int r, int v , int idx , int lx , int rx){
            propagate(idx,lx,rx);
            if(lx >= r || rx <= l) return;
            if(lx >= l && rx <= r){
                lazy[idx] = operation( lazy[idx] , v , 1);
                seg[idx] = operation( seg[idx] , v ,  rx - lx); 
                return;
            }
            int m = (lx + rx) / 2;
            _add(l , r , v , idx * 2 + 1 , lx , m);
            _add(l , r , v , idx * 2 + 2 , m , rx);

            seg[idx] = merge( seg[2 * idx + 1] , seg[2 * idx + 2] );

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
             seg = vector<item>( size<<1 , 0 );
             lazy = vector<int>( size<<1 , NO_OPERATION );
         
        }

       
 
        void add(int l,int r , int v){
            _add(l,r,v,0,0,size);
        }
     
 
        int query(int l , int r ){
            return _query(l,r ,  0 , 0 ,size);
 
        }
 
        int get(int i){
            return _get(i,0,0,size); 
        }
 
        
 
     
};



signed main() {
  
    return 0;
}
