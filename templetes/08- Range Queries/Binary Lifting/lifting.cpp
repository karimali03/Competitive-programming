struct BinaryLifting {
    int n;
    int LOG;
    int dummy;
    vector<vector<int>> jmp;

    // next_node[i] should contain the destination of 1 step from node i.
    // dummy_node is the "out of bounds" index (e.g., n + 1 for jumping right, 0 for left).
    BinaryLifting(int n, const vector<int>& next_node, int dummy_node) {
        this->n = n;
        this->dummy = dummy_node;
        
        // Calculate the maximum power of 2 needed for n elements
        LOG = 0;
        while ((1 << LOG) <= n) {
            LOG++;
        }
        // Alternatively, use a fixed size like LOG = 20 for n <= 10^6

        // Initialize table: jmp[node][k]
        // Default everything to the dummy node to avoid out-of-bounds errors
        jmp.assign(n + 2, vector<int>(LOG, dummy));

        // STEP 1: Base Case (2^0 = 1 jump)
        for (int i = 1; i <= n; i++) {
            jmp[i][0] = next_node[i];
        }

        // STEP 2: Build the Table
        // OUTER LOOP MUST BE 'k' (the power of 2)
        for (int k = 1; k < LOG; k++) {
            // INNER LOOP is the starting node 'i'
            for (int i = 1; i <= n+1 ; i++) { 
                int halfway = jmp[i][k - 1];
                jmp[i][k] = jmp[halfway][k - 1];
            }
        }
    }

    // STEP 3: The Query (Jump as far as possible without passing the target)
    // Returns the total number of jumps required to reach or stay behind the target.
    int count_jumps_to_target(int start, int target) {
        int curr = start;
        int jumps = 0;

        // Iterate k BACKWARDS from largest to smallest
        for (int k = LOG - 1; k >= 0; k--) {
            // Condition to check if this jump is valid.
            // Example: jumping right, we want to stay <= target
            if (jmp[curr][k] <= target) { 
                curr = jmp[curr][k]; // Make the jump
                jumps += (1 << k);   // Add 2^k steps to our counter
            }
        }
        
        return jumps;
    }

    // Alternative Query: Just find where you land after exactly 'x' steps
    int jump_exactly(int start, int x) {
        int curr = start;
        for (int k = 0; k < LOG; k++) {
            // If the k-th bit of x is 1, we need to take a jump of size 2^k
            if ((x >> k) & 1) {
                curr = jmp[curr][k];
            }
        }
        return curr;
    }
};

