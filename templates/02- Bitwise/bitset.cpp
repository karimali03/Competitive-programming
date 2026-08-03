// Return possible subset sums for nonnegative values up to maxSum.
// possible[s] is 1 iff some subset has sum s. Sums above maxSum are ignored.
// Use this when maxSum is known at runtime or you do not want a template.
vector<char> possibleSubsetSums(const vector<int>& values, int maxSum) {
    assert(maxSum >= 0);
    vector<char> possible(maxSum + 1, 0);
    possible[0] = 1;

    for (int value : values) {
        assert(value >= 0);
        for (int sum = maxSum; sum >= value; --sum) {
            possible[sum] = possible[sum] || possible[sum - value];
        }
    }

    return possible;
}

// Return true if target can be formed as a subset sum of nonnegative values.
// Use when you only need one target answer.
bool canMakeSubsetSum(const vector<int>& values, int target) {
    assert(target >= 0);
    return possibleSubsetSums(values, target)[target];
}

// Return all reachable subset sums up to maxSum.
// Use when you need to iterate over the actual sums instead of checking a bit.
vector<int> listSubsetSums(const vector<int>& values, int maxSum) {
    vector<char> possible = possibleSubsetSums(values, maxSum);
    vector<int> sums;
    for (int sum = 0; sum <= maxSum; ++sum) {
        if (possible[sum]) sums.push_back(sum);
    }
    return sums;
}
