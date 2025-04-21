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

void solve(int test_case){
    int n; cin>>n;
    vii v(n,vi(n));
    f(i,0,n) cin>>v[i];
    vi a(n),b(n); cin>>a>>b;   
    vi asuf(n),apre(n);
    vi bsuf(n),bpre(n);
    apre[0] = a[0]; bpre[0] = b[0];
    asuf[0] = a[n-1]; bsuf[0] = b[n-1];
    for(int i  = 1 ; i < n ; i++){
        apre[i] = a[i];
        for(int x = 0 ; x < n ; x++){
            if(v[i-1][x]-v[i][x] == 1){
                 apre[i] += apre[i-1];
            }
        }
    }
    for(int i  = 1 ; i < n ; i++){
        bpre[i] = b[i];
        for(int x = 0 ; x < n ; x++){
            if(v[x][i-1]-v[x][i] == 1){
                 bpre[i] += bpre[i-1];
            }
        }
    }

    for(int i = n-2 ; i>= 0 ; i--){
        bsuf[i] = b[i];
        for(int x = 0 ; x < n ; x++){
            if(v[x][i+1]-v[x][i] == 1){
                 bpre[i] += bpre[i+1];
            }
        }
    }

    for(int i = n-2 ; i>= 0 ; i--){
        asuf[i] = a[i];
        for(int x = 0 ; x < n ; x++){
            if(v[i+1][x]-v[i][x] == 1){
                 apre[i] += apre[i+1];
            }
        }
    }

    vi resa(n),resb(n);
    for(int i = 0 ; i < n-1 ; i++){
        bool conf = false;
        for(int x = 0 ; x < n  ;x++){
            if(v[i][x] == v[i+1][x]) conf = true;
        }
        if(conf){
            if(i+2 < n){
                for(int x = 0 ; x < n  ;x++){
                    if(v[i+1][x] == v[i+2][x]) conf = false;
                }
            }
            if(!conf) resa[i] += asuf[i+2];
        }
    }


}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}