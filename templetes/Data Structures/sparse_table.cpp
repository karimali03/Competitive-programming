#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct sparse {
	vector<vector<int>>m;
	sparse(vector<int>&v){
		int n = v.size();
		m = vector<vector<int>>(n,vector<int>(20));
			
		for(int i = 0; i < n; i++) {
			m[i][0] = v[i];
		}
		// 2) preprocessing, O(N*log(N))
		for(int k = 1; k < 20; k++) {
			for(int i = 0; i + (1 << k) - 1 < n; i++) {
				m[i][k] = (m[i][k-1] + m[i+(1<<(k-1))][k-1]);
			}
		}
	}
	
	int query(int L, int R) { // O(1)
		int len = R - L + 1;
		int k = 31 - __builtin_clz(len);
		return max(m[L][k], m[R-(1<<k)+1][k]);
	}
	
	int query_sum(int L, int R) { // O(logn)
		int sum = 0;
		for( int i = L ;  i <= R ;){
			int k = 31 - __builtin_clz(R-i+1);
			sum+=m[i][k]; 
			i+=(1<<k);
			
		}
		return sum;
	}
	
};
