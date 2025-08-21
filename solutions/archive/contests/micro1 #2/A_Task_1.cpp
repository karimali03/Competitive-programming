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

vi v;

void solve(int test_case){
    v = vi(5); cin>>v;
    int sum = 0;
    f(i,0,5) sum+=v[i];
    for(int i = 0 ; i < 5 ; i++){
        sum-=v[i];
        f(j,0,5){
            if(j == i) continue;
            if(sum - v[j] == v[i]){
                int points = v[j];
                // 3 0 1
                for(int x = 0 ; x < 5 ; x++){
                    if(x == i || x == j) continue;
                    int cur = v[x]*3;
                    for(int y = 0 ; y < 5 ; y++){
                        if(y == x || y == i || y == j) continue;
                        if(cur + v[y] == points){
                            int re = 1+2+3+4 - (i+j+x+y);
                         //   cout<<re<<"--"<<ln;
                        //    print(i,j,x,y);
                            cout<<v[i]<<" "<<v[x]<<" "<<v[y]<<" "<<v[re]<<" "<<v[j]<<ln;
                            return;
                        }
                    }

                }
            }
        }
        sum+=v[i];
    }
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