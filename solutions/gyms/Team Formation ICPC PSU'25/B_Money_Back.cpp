#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int zeros = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == 0) zeros++;
    }
 
    int totalTeams = n / 3;
    // Each team with any zero can't take discount.
    // So we need to put max zeros together to minimize expensive teams.
 
    int fullPriceTeams = (zeros + 2) / 3; // ceil(zeros / 3)
    int discountedTeams = totalTeams - fullPriceTeams;
 
    int totalCost = fullPriceTeams * 3000 + discountedTeams * 2000;
    cout << totalCost << '\n';
}
