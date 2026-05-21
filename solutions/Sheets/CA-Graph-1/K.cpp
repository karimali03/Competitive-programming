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


void kemo() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int ask(int i,int j){
    cout<<"? "<<i<<" "<<j<<endl;
    cout.flush();
    int ret; cin>>ret;
    return  ret;
}


map<int,vi>mp;
map<int,int>vis;

void dfs(int i){
	vis[i] = 1;
	cout<<i<<" ";
	for(auto x : mp[i]){
		if(!vis[x]) dfs(x);
	}
}

void solve(int test) {
	int n; cin>>n;

	
	f(i,0,n){
		int x,y; cin>>x>>y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	}
	for(auto [x,y]: mp){
		if(y.size() == 1){
			dfs(x);
			return;
		}
	}
}

signed main() {
    kemo();
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}