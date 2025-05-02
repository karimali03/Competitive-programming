#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

// Variadic print function for debugging
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

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}


int ask(int x,int y){
    cout<<"? "<<x<<" "<<y<<endl;
    int ret; cin>>ret;
    return  ret;
}


void solve(int test_case){
    int n;  cin>>n;
    vi res(n+1,-1);
    vi found(n+1);
    int prev = 1;
    for(int i = 1 ; i <= n - 1 ; i++){
        int x = ask(prev,i+1);
        int y = ask(i+1,prev);
        if(x > y){
            res[prev] = x;
            found[x] = 1;
            int c = 0;
            int val = 0;
            for(int a = x + y ; a <= n ; a+=x ){
                if(!found[a]) c++,val=a;
            }
            if(c == 1){
                res[i+1] = val;
                found[val] = 1;
                prev = i+2; i++;
            }
            else prev = i+1;
        }
        else{
            res[i+1] = y;
            found[y] = 1;
            int c = 0;
            int val = 0;
            for(int a = x + y ; a <= n ; a+=y ){
                if(!found[a]) c++,val=a;
            }
            if(c == 1){
                res[prev] = val;
                found[val] = 1;
                prev = i+2; i++;
            }
        }
    }
    int val = 0;
    for(int i = 1 ; i <= n ; i++) if(!found[i]) val=i;
    for(int i  =1 ; i <= n  ;i++){
        if(res[i] == -1){
            res[i] = val;
        }
    }

    cout<<"! ";
    for(int  i =1 ; i <= n ;i++) cout<<res[i]<<" ";
    cout<<endl;


}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}