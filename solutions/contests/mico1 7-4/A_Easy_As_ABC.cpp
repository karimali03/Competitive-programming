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

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

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

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}


vi di = {0,-1,-1,-1,0,1,1,1};
vi dj = {1,1,0,-1,-1,-1,0,1};
string mn;
string cur_s;
int vis[3][3]{};
void calc(vector<string>&v ,int i,int j, int cur = 0){
    if (cur == 3){
        mn = min(mn,cur_s);
        return;
    }
    for(int d = 0 ; d < 8 ; d++){
        int dx = i + di[d];
        int dy = j + dj[d];
        if(dx >= 0 && dy >= 0 && dx < 3 && dy < 3 
        && !vis[dx][dy] ){
            vis[dx][dy] = 1;
            cur_s.push_back(v[dx][dy]);
            calc(v,dx,dy,cur+1);
            vis[dx][dy] = 0;
            cur_s.pop_back();
        }
    }
}
void solve(int test_case){
    vector<string>s(3);
    f(i,0,3) cin>>s[i];
    mn = s[0];
    for(int i = 0 ; i  < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            calc(s,i,j,0);
        }
    }
    cout<<mn<<"\n";
}