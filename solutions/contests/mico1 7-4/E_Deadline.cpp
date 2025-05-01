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


vector<int> topsort(vii &adjList , vi &d , vi&c) {	// O( E+V )
	int sz = adjList.size();
	vector<int> indegree(sz, 0);	// compute indegrees of nodes
	for (int i = 0; i < sz; ++i)
		for (int j : adjList[i])
			indegree[j]++;
    int time = 0 ;
	priority_queue< vi , vii , greater<> > ready;	// add all current nodes that has indegree(0)
	for (int i = 0; i < sz; ++i)
		if (!indegree[i])
			ready.push({d[i] ,i});
    
	vector<int> ordering;
	while (!ready.empty()) {	// keep picking a ready node
		auto i = ready.top();
		ready.pop();
     //   cout<<i.second<<" "<<i.first<<" "<<time<<"\n";
        if( time + c[i[1]] > i[0] ) return {};
        time += c[i[1]];
		ordering.push_back(i[1]);

		for (int j : adjList[i[1]])	// remove its outgoing edges
			if (--indegree[j] == 0)	// If a neighbor is ready, add it
				ready.push({ d[j] ,j});
	}
	if (ordering.size() != adjList.size())
		ordering.clear();				//There are cycles
	return ordering;
}


void solve(int test_case){
    int n; cin>>n;
    vii adj(n);
    vi d(n),c(n);
    vi mn(n , INT64_MAX );
    for(int i = 0 ; i < n ; i++){
        cin>>d[i]>>c[i];
        int r; cin>>r;
        for(int x = 0 ; x < r ; x++){
            int a; cin>>a; a--;
            adj[a].push_back(i);
        }
    }
 

    auto res = topsort(adj,d,c);
    if(res.empty()) cout<<"NO"<<ln;
    else {
        cout<<"YES"<<ln;
        for(auto it : res) cout<<it+1<<" ";
        cout<<ln;
    }
}