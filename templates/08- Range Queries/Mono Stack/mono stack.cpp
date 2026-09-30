vector<int> NGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,n);
    for(int i = 0 ; i < n ; i++){
        while(!st.empty() && v[st.top()] < v[i]){ // > for NSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> PGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,-1);
    for(int i = n-1 ; i >= 0 ; i--){
        while(!st.empty() && v[st.top()] < v[i]){ // > for PSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}


vector<int> kth_NGE(vector<int> &v , int k){
    int n = v.size();
    vector<int>res(n,n);
    vector<stack<int>>st(k);
    for(int i = 0 ; i <  n ;i++){
        for(int j = k-1 ; j >= 0 ;j--){
            stack<int> cur;
            while(!st[j].empty() && v[st[j].top()] < v[i]){ // > for NSE
                cur.push(st[j].top()); 
                st[j].pop();
            }
            while(!cur.empty()){
                auto idx = cur.top(); cur.pop();
                if(j == k-1) res[idx] = i;
                else st[j+1].push(idx);
            }
        }
        st[0].push(i);
    }
    return res;
}

vector<int> kth_PGE(vector<int> & v , int k){
    int n = v.size();
    vector<int>res(n,-1);
    vector<stack<int>>st(k);
    for(int i = n-1 ; i >= 0 ;i--){
        for(int j = k-1 ; j >= 0 ;j--){
            stack<int> cur;
            while(!st[j].empty() && v[st[j].top()] < v[i]){ // > for NSE
                cur.push(st[j].top()); 
                st[j].pop();
            }
            while(!cur.empty()){
                auto idx = cur.top(); cur.pop();
                if(j == k-1) res[idx] = i;
                else st[j+1].push(idx);
            }
        }
        st[0].push(i);
    }
    return res;
}




// count Subaarays with  mn >= k
auto calc = [&](int mn,int limit){
        vi wl(n,-1),wr(n,n);
        int lst = -1;
        for(int i = 0;i < n ; i++){
            if(v[i] < limit) lst = i;
            wl[i] = lst;
        }
        lst = n;
        for(int i = n-1 ; i >= 0 ; i--){
            if(v[i] < limit) lst = i;
            wr[i] = lst;
        }
        int ret = 0;
        for(int i = 0;i < n ; i++){
            int len = v[i] * mn;
            int L = max(pg[i]+1,wl[i]+1);
            int R = min(ng[i]-1,wr[i]-1);
            // [L,R] mx = mx , mn >= limit
            int lx = max(i - len + 1 , L);
            int ly = min(i , R - len + 1);
            if(lx <= ly) ret += (ly-lx+1);
        }
        return ret;
};
// calc(mn,mn) - calc(mn,mn+1) -> subarray with mn = mn exatctly
