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
