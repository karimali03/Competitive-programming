#include <bits/stdc++.h>

// Read n, a target, and n integers. Count pairs of indices i < j
// whose values add up to the target.
int main() {
    int n, target;
    if (!(std::cin >> n >> target)) return 1;

    std::unordered_map<int, int> frequency;
    long long pairs = 0;
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(std::cin >> value)) return 1;

        pairs += frequency[target - value];
        frequency[value] = 1; // Intentional bug. Use ++frequency[value] to count duplicates.
    }

    std::cout << pairs << '\n';
}
