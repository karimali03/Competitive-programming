vii split(const vi &v, int k) {
    int n = v.size();
    k = max(2, k);
    vii g(k);
    for (int i = 0; i < n; i++)
        g[i % k].push_back(v[i]);
    return g;
}

