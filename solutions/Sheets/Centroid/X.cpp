// Count pair (i,j) where i < j 
// Ai + Aj <= x AND Bi + Bj <= y
long long countPairs(vector<pair<int,int>> p, long long x, long long y) {
    int n = p.size();
    vector<pair<long long, long long>> queries;
    vector<long long> coords;
 
    for (auto [a, b] : p) {
        queries.push_back({x - a, y - b});
        coords.push_back(b);
    }
 
    sort(p.begin(), p.end());
    sort(queries.begin(), queries.end());
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
 
    int m = coords.size();
    vector<int> bit(m + 1, 0);
 
    auto add = [&](int i) {
        for (; i <= m; i += i & -i)
            bit[i]++;
    };
 
    auto query = [&](int i) {
        int ans = 0;
        for (; i > 0; i -= i & -i)
            ans += bit[i];
        return ans;
    };
 
    long long ans = 0;
    int j = 0;
 
    for (auto [A, B] : queries) {
        while (j < n && p[j].first <= A) {
            int idx = lower_bound(coords.begin(), coords.end(),
                                  p[j].second) - coords.begin() + 1;
            add(idx);
            j++;
        }
 
        int idx = upper_bound(coords.begin(), coords.end(), B)
        - coords.begin();
        ans += query(idx);
    }
 
    for (auto [a, b] : p) {
        if (a <= x - a && b <= y - b)
            ans--;
        }
 
        return ans / 2;
}