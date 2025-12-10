    // O(26 * n)  
    string s; cin>>s;
    int cnt[26]{};
    for(int i = 0;i < s.size() ; i++) cnt[s[i]-'a']++;
    string sorted;
    for(int i = 0 ;i < 26 ; i++){
        while(cnt[i]--) sorted.push_back((char)(i+'a'));
    }
