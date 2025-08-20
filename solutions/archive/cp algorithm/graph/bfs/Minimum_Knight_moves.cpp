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
int di[] {2,2,1,1,-2,-2,-1,-1};
int dj[] {1,-1,2,-2,1,-1,2,-2};

void solve(int test_case){
    string a,b; cin>>a>>b;
  //  cout<<a<<" "<<b<<ln;
    queue<pair<int,int>>q;
    int vis[8][8]{};
    q.push({a[0]-'a',a[1]-'0'-1});
    vis[a[0]-'a'][a[1]-'0'-1] = 1;
    int cnt = 0;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto cur = q.front(); q.pop();
            if(cur.first == (b[0]-'a') && cur.second == (b[1]-'0'-1))
            return void(cout<<cnt<<ln);
            for(int d = 0 ; d < 8 ; d++){
                int x = di[d] + cur.first;
                int y = dj[d] +cur.second;
                if(x>=0 && y>=0 && x<8&&y<8&&!vis[x][y]){
                    q.push({x,y});
                    vis[x][y] =1;
                }
            }
        }
        cnt++;
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