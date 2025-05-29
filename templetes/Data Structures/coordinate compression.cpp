struct compress {
    vector<int> org;
    map<int,int>mp;
    int sz;
    compress(vector<int> v){
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        f(i,0,v.size()) mp[v[i]] = i;
        for(auto [a,b] : mp) org.push_back(a);
        sz = v.size();
    }
    int idx(int val){
        return mp[val];
    }

    int val(int idx){
        return org[idx];
    }
};
