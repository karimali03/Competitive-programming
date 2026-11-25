#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 4) return 1;

    ifstream input(argv[1]);
    ifstream output(argv[2]);
    ifstream answer(argv[3]);

    int n, target;
    if (!(input >> n >> target) || n < 0) return 1;

    vector<int> values(n);
    for (int& value : values) {
        if (!(input >> value)) return 1;
    }

    long long actual, expected;
    if (!(output >> actual) || !(answer >> expected)) return 1;

    std::string extra;
    if (output >> extra) return 1;
    return actual == expected ? 0 : 1;
}
