int atMostK(vector<int>& a, int k) {
    map<int,int> freq;
    int l = 0, res = 0;
    for (int r = 0; r < a.size(); r++) {
        freq[a[r]]++;
        while (freq.size() > k) {
            if (--freq[a[l]] == 0) freq.erase(a[l]);
            l++;
        }
        res += (r - l + 1); // all subarrays ending at r
        // 1. Both l and r only move forward -> O(n)
        // 2. At this point, window [l, r] is valid (at most k distinct)
        // 3. All subarrays ending at r and starting anywhere from l..r are valid
        //    -> there are (r - l + 1) such subarrays
    }
    return res;
}
// To get exactly K distinct subarrays:
// exactlyK = atMostK(a, K) - atMostK(a, K-1);


// cnt[1..M] = frequency/value at each circular position
// Need the minimum circular segment containing at least NEED items
int circular_two_pointer(vector<int>& cnt, int M, int NEED) {
    int best = M;
    int r = 1;
    int sum = 0;
    for (int l = 1; l <= M; l++) {
        // Expand right pointer until condition is satisfied
        while (r < l + M && sum < NEED) {
            int pos = (r - 1) % M + 1; // int pos = r % n; (0 indexed)
            sum += cnt[pos];
            r++;
        }
        // Current window is [l, r)
        if (sum >= NEED) {
            best = min(best, r - l);
        }
        // Remove left position before l moves
        sum -= cnt[l];
    }

    return best;
}
