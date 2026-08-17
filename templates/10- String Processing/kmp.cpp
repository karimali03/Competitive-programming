// pi[i] = longest proper prefix of s that is also suffix of s[0..i]
// on mismatch: jump to next smaller border using pi[j-1]
vector<int> prefix_function(const string &s){
    int n = s.size();
    vector<int> pi(n);
    int j = 0;

    for(int i = 1; i < n; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }

    return pi;
}


// cnt[len] = number of occurrences of prefix s[0..len-1] in s
// propagate occurrence of a prefix to all its borders
vi prefix_substr(const string &s){
    int n = s.size();
    vi cnt(n+1);

    auto pi = prefix_function(s);

    for(int i = 0; i < n; i++)
        cnt[pi[i]]++;

    for(int len = n; len > 0; len--)
        cnt[pi[len-1]] += cnt[len];

    // every prefix occurs once as itself
    for(int len = 1; len <= n; len++)
        cnt[len]++;

    return cnt;
}


// aut[state][c] = matched prefix length after adding char c
// precomputes KMP fallback; state n = full match
vii prefix_function_automaton(const string &s){
    int n = s.size();
    vii aut(n+1, vi(26));

    if(n == 0) return aut;

    auto pi = prefix_function(s);

    aut[0][s[0]-'a'] = 1;

    for(int i = 1; i < n; i++){
        for(int c = 0; c < 26; c++){
            if(c == s[i]-'a')
                aut[i][c] = i+1;
            else
                aut[i][c] = aut[pi[i-1]][c];
        }
    }

    // allow continuing after a full match (overlapping matches)
    for(int c = 0; c < 26; c++)
        aut[n][c] = aut[pi[n-1]][c];

    return aut;
}


// returns all 0-based positions where pattern s occurs in text t
// use s + '#' + t, full match when pi[i] == |s|
vector<int> find_substr(const string &s, const string &t){
    int n = s.size();

    string cur = s + '#' + t;
    auto pi = prefix_function(cur);

    vi ret;

    for(int i = n+1; i < (int)cur.size(); i++){
        if(pi[i] == n)
            ret.push_back(i - 2*n);
    }

    return ret;
}


// O(n^2) count distinct substrings
// when adding new char, only suffixes are new candidates
// reverse -> suffixes become prefixes
// new substrings = len - max(pi)
ll count_different_substrings(const string &s){
    ll ans = 0;
    string cur;

    for(char c : s){
        cur.push_back(c);

        string rev = cur;
        reverse(rev.begin(), rev.end());

        auto pi = prefix_function(rev);

        int mx = 0;
        for(int x : pi) mx = max(mx, x);

        ans += (int)cur.size() - mx;
    }

    return ans;
}
