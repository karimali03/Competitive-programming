int compute_mex(vector<int> &values) {
    int n = int(values.size());
    vector<bool> seen(n + 1, false);
 
    for (const auto &x : values)
        if (x <= n)
            seen[x] = true;
 
    int mex = 0;
 
    while (seen[mex])
        mex++;
 
    return mex;
}