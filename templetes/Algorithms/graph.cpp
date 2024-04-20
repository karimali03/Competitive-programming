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
 



class graph {
	public:
	vector<vector<int>> v;
	vector<int> vis;
	int n;
    
	graph(int n) : n(n){
		v = vector<vector<int>>(n);
		vis = vector<int>(n);
	}
	
	void clear(){
		vis.clear();
	}
	
	void dir(int x,int y){
		v[x].push_back(y);
	}
	
	void un_dir(int x,int y){
		v[x].push_back(y);
		v[y].push_back(x);
	}
	
	bool cycle(int x,int y){
		vis[x] = 1;
		bool cyc = false;
		for(auto it : v[x]){
			if(it == y) continue;
			if(!vis[it]) cyc|=cycle(it,x);
			else cyc = true;
		}
		return cyc;
	}
	
	bool tree(){
		if(cycle(0,-1)) return false;
		for(int i = 1;i < n ;i++) if(!vis[i]) return false;
		return true;
	}

	bool biprate(int x,int y, int sw = 1){
		vis[x] = sw;
		sw = sw == 1 ? 2 : 1;
		bool ret = true;
		for(auto it : v[x]){
			
			if(it == y) continue;
			if(!vis[it]) ret&= biprate(it,x,sw);
			else if(vis[it] != sw) ret = false;
			
		}
		return ret;
	}

	void dfs(int x,int y){
		vis[x] = 1;
		
		for(auto it : v[x]){
			if(it == y) continue;
			if(!vis[it]) dfs(it,x);
		}
	}

	vi bfs(int start){
		queue<int>q;
		vi len(n,-1);
		q.push(start);
		len[start] = 0;
		for(int sz = 1 , lvl = 0 ; !q.empty(); sz = q.size() , lvl++){

			while(sz--){
				int x = q.front();
				q.pop();
				for(auto it : v[x]){
					if(len[it] == -1){
						q.push(it);
						len[it] = lvl + 1;
					}
				}
			}

		}

		return len;
	}
	
};


/*
operations problems : 
	give object -> do op -> get object -> do op
	objects are nodes , operations are edges
*/
