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
 
 
void solve(int test_case){
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    int  j = 0;
    int sum = 0;
    int cnt = 0;
    for(int i = 0 ; i < n ;i++){
        sum+=v[i];
        while (sum - v[j] >= k )
        {
            if(i - j <= 1 && v[j] < k  ) cnt++;
            sum-=v[j];
            j++;
        }
      
    }

    cout<<cnt<<ln;
}
 
signed main() {
    kemo();
    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
 
    return 0;
}
