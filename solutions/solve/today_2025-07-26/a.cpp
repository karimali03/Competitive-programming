#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

int hammingDistance(const string &a, const string &b) {
    int distance = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            distance++;
        }
    }
    return distance;
}

string findBestString(int n, int k, const vector<string> &friends) {
    string bestStr(k, '0');
    int maxMinDistance = -1;

    // Iterate all possible strings in lexicographical order
    for (int mask = 0; mask < (1 << k); ++mask) {
        string currentStr(k, '0');
        for (int i = 0; i < k; ++i) {
            if (mask & (1 << (k - 1 - i))) {
                currentStr[i] = '1';
            }
        }

        int minDistance = INT_MAX;
        for (const string &friendStr : friends) {
            int distance = hammingDistance(currentStr, friendStr);
            if (distance < minDistance) {
                minDistance = distance;
                if (minDistance <= maxMinDistance) {
                    break; // No need to check further for this string
                }
            }
        }

        if (minDistance > maxMinDistance) {
            maxMinDistance = minDistance;
            bestStr = currentStr;
        } else if (minDistance == maxMinDistance) {
            if (currentStr < bestStr) {
                bestStr = currentStr;
            }
        }
    }

    return bestStr;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<string> friends(n);
    for (int i = 0; i < n; ++i) {
        cin >> friends[i];
    }

    string result = findBestString(n, k, friends);
    cout << result << endl;

    return 0;
}