long long compute_hash(string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// custom hash
struct HASH{
    size_t operator()(const pair<int,int>&x)const{
        return ((long long)x.first) ^ ((long long)x.second << 32);
    }
};
unordered_set<pair<int,int>, HASH> st;

