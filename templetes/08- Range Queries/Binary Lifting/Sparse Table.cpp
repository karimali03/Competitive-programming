 struct sparse {
	vector<vector<int>> mn, mx;
	int n;
 
	sparse(vector<int>& v) {
		n = v.size();
		int LOG = 64 - __builtin_clzll(n); // ensures log2(n) + 1
		mn = mx  = vector<vector<int>>(n, vector<int>(LOG));
 
		for (int i = 0; i < n; i++) {
			mn[i][0] = mx[i][0] = v[i];
		}
 
		for (int k = 1; (1 << k) <= n; k++) {
			for (int i = 0; i + (1 << k) <= n; i++) {
				mn[i][k] = min(mn[i][k - 1], mn[i + (1 << (k - 1))][k - 1]);
				mx[i][k] = max(mx[i][k - 1], mx[i + (1 << (k - 1))][k - 1]);	
			}
		}
	}
 
	int query_min(int L, int R) {
		int k = 63 - __builtin_clzll(R - L + 1);
		return min(mn[L][k], mn[R - (1 << k) + 1][k]);
	}
 
	int query_max(int L, int R) {
		int k = 63 - __builtin_clzll(R - L + 1);
		return max(mx[L][k], mx[R - (1 << k) + 1][k]);
	}
 
	
};
