// Function to calculate the contribution of each distinct value in the range [i, n-1]
// works for or , and , gcd, lcm etc. depending on how the sparse table is built
void calc(int n, sparse& spt) {
    int max_k = 20; 

    for (int i = 0; i < n; i++) {
        int l = i; // Starting index of the range we are currently evaluating
        
        while (l < n) {
            int cur = spt.query(i, l); 
            int r = l; 
            
            // find the maximum 'r' such that spt.query(i, r) == cur
            for (int k = max_k; k >= 0; k--) {
                if (r + (1 << k) < n && spt.query(i, r + (1 << k)) == cur) {
                    r += (1 << k);
                }
            }

            // Move 'l' past 'r' to find the next distinct value
            l = r + 1; 
        }
    }
}
