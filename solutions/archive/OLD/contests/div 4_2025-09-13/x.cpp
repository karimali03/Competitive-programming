#include <bits/stdc++.h>

using namespace std;


void fastIO(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

typedef long long ll;
#define int ll

void solve(int tc) {

    int n; cin >> n;

    vector<vector<int>> s;

    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        vector<int> v(k);
        for (int j = 0; j < k; ++j) {
            cin >> v[j];
        }
        s.push_back(v);
    }
    sort(s.begin(), s.end());

    while (!s.empty()) {
        vector<int> v = *s.begin();
        s.erase(s.begin());

        for(auto &ele : v) cout << ele << ' ';


        vector<vector<int>> new_s;
        for(auto &vv : s) {
            if(v.size() < vv.size())
                new_s.push_back(vector<int>{vv.begin() + v.size(), vv.end()});
        }
        s = new_s;
        std::sort(s.begin(), s.end());

    }

    cout << '\n';
}

signed main() {

    fastIO(); 
    cout << setprecision(10) << fixed;
    int t = 1; cin >> t;

    for (int i = 1; i <= t; ++i)
        solve(i);

    return 0;
}