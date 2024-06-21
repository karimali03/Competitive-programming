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
 
void kemo(int read = 1) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if(read){
		#ifndef ONLINE_JUDGE
				freopen("in.txt", "r", stdin);
				freopen("out.txt", "w", stdout);
		#endif
    }
}
 
int ask(int i,int j){
    cout<<"? "<<i<<" "<<j<<endl;
    cout.flush();
    int ret; cin>>ret;
    return  ret;
}
 
struct item{
   vi v;
   item (vi & v):v(v){}

};
 
struct segment_tree
{
    private:
        int size;
 
        vector<item> seg;
        vi neu = {INT_MAX};
        item neutral = {  neu  };
 
        item merge(item &x , item &y){

            int i = 0 , j = 0 , k = 0;
            int sz1 = (int)x.v.size();
            int sz2 = (int)y.v.size();
            vi ret = vi(sz1+sz2);
            while( i < sz1 && j < sz2){
                if(x.v[i] < y.v[j]){
                    ret[k++] = x.v[i++];
            }
            else{
                ret[k++] = y.v[j++];
            }
            }
            while(i < sz1){
                ret[k++] = x.v[i++];
            }
            while(j < sz2){
                ret[k++] = y.v[j++];
            }

            return item{ret};

        }
 
         item single(int v){
            vi arr = {v};
            return item{arr};
        }

        int calc(item & a , int k){
            return upper_bound(all(a.v) , k) - a.v.begin();
        }


        void _build(vi & v,int idx , int lx , int rx){
            if(rx - lx == 1){
                if(lx < (int)v.size()){
                    seg[idx] = single(v[lx]);
                }
                return;
            }
            int m = (lx + rx) / 2;
            _build(v , idx * 2 + 1 , lx , m);
            _build(v , idx * 2 + 2 , m , rx);
            seg[idx] = merge(seg[2 * idx + 1] , seg[2 * idx + 2]);
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
 
 
        int _query(int l , int r , int k , int idx , int lx , int rx){
            if(lx >= r || rx <= l) return 0;
            if(lx >= l && rx <= r){
           
                return calc(seg[idx] , k);
            }
            int m = (lx + rx) / 2;
            int s1 = _query(l , r , k , idx * 2 + 1 , lx , m);
            int s2 = _query(l , r , k , idx * 2 + 2 , m , rx);
            return  ( s1 +  s2 );
        }


    
    public:
          segment_tree(int n){
            size = 1;
            while (size < n)
            {
                size<<=1;
            }
             seg = vector<item>( size<<1 , neutral );
 
        }

        void build(vi & v){
            _build(v,0,0,size);
        }

        void set(int i , int v){
            assert(i >=0 && i < size);
            _set(i,v,0,0,size);
        }
 
        int query(int l , int r , int k){
            return _query(l , r, k , 0,0,size);
        }
 
       
  
};
 
 
 
void solve(int test_case){
   

}
 
signed main() {
    kemo();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
 
    return 0;
}
