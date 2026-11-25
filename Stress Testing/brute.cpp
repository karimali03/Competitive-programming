#include <bits/stdc++.h>

int main() {
    int n, target;
    if (!(std::cin >> n >> target)) return 1;

    std::vector<int> values(n);
    for (int& value : values) {
        if (!(std::cin >> value)) return 1;
    }

    long long pairs = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (values[i] + values[j] == target) ++pairs;
        }
    }

    std::cout << pairs << '\n';
}
