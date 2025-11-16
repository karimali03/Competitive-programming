vector<int> prefix_function(string &s){
    int n = s.size();
    vector<int>pi(n);
    int j = 0;
    for(int i = 1;i < n ; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j-1]; 
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// Count how many times each prefix occurs as a substring
vi prefix_substr(string &s){ 
    int n = s.size();
    vi frq(n+1);
    auto pi = prefix_function(s);
    for(int i=0;i<n;i++) frq[pi[i]]++;
    for(int i=n-1;i>0;i--) frq[pi[i-1]] += frq[i];
    for(int i=0;i<=n;i++) frq[i]++;
    return frq;
}


// aut[i][j] = pi val of suffix end with char j and prev pi is i
// way to "de-amortize" the standard KMP prefix function calculation.
vii prefix_function_automaton(string &s){
    int n = s.size();
    auto pi = prefix_function(s);
    vii aut(n,vi(26));
    aut[0][s[0]-'a'] = 1;
    for(int i = 1 ;i < n ; i++){
        for(int j = 0; j < 26 ; j++){
            if(j == (s[i]-'a')) aut[i][j] = i+1;
            else aut[i][j] = aut[pi[i-1]][j];
        }
    }
    return aut;
}

// count each occurence of s as substr in t
vector<int> find_substr(string &s,string &t){
    string cur = s + '#' + t;
    int n = s.size();
    int m = t.size();
    int sz = cur.size();
    cout<<cur<<ln;
    auto pi = preifx_function(cur);
    vi ret;
    for(int i = n+1 ; i < sz ; i++){
        if(pi[i] == n)  ret.push_back(i - 2*n);
    }
    return ret;
}


ll count_different_substrings(string& s) { // O(n^2)
    int n = s.length();
    ll total_unique_count = 0;
    string current_prefix = "";

    // Iterate, adding one character at a time
    for (int i = 0; i < n; i++) {
        current_prefix.push_back(s[i]); // s_current = s_current + c

        // t = s_current + c (which is just current_prefix)
        // Reverse t to get t_rev
        string reversed_t = current_prefix;
        reverse(reversed_t.begin(), reversed_t.end());

        // Compute the prefix function for the reversed string
        vector<int> pi = compute_pi(reversed_t);

        // Find the maximum value in the prefix function array
        int pi_max = 0;
        if (!pi.empty()) {
            pi_max = *max_element(pi.begin(), pi.end());
        }

        // The number of new substrings is |t| - pi_max
        long long new_substrings = current_prefix.length() - pi_max;

        // Add to the total
        total_unique_count += new_substrings;
    }

    return total_unique_count;
}


