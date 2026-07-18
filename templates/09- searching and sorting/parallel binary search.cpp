  int n; cin>>n;
    vector<array<int,2>> h(n);
    f(i,0,n){
        int x; cin>>x;
        h[i] = {x,i};
    }
    sort(rall(h));
    
    int q; cin>>q;
    vector<array<int,3>> x(q);
    f(i,0,q){
        int l,r,w; cin>>l>>r>>w; l--,r--;
        x[i] = {w , l , r};
    }
 
    // current l,r,ans for each query
    vector<int> L(q),R(q),ans(q);
    // buckets for each mid value ; store query indices
    vii buckets(n);
    f(i,0,q) L[i]=0,R[i]=n-1;
    // returns true if there are still queries to process
    auto update = [&]() -> bool{
        bool vld = false;
        for(int i = 0;i < q ; i++){
            if(L[i] <= R[i]){
                buckets[(L[i]+R[i])>>1].push_back(i);
                vld = true;
            }
        }
        return vld;
    };

    SegmentTree st(n);
    while(update()){
        st.build(n);
        // process each mid value
        for(int mid = 0; mid < n ; mid++){
            // update segment tree with current mid value
            st.update(h[mid][1],1);
            // process queries in the bucket for this mid
            for(auto &idx : buckets[mid]){
                auto [w,l,r] = x[idx];
                if(st.query(l,r).ans >= w){
                    ans[idx] = h[mid][0];
                    R[idx] = mid - 1;
                }else{
                    L[idx] = mid + 1;
                }
            }
            // clear bucket for next iteration
            buckets[mid].clear();
        }
    }

    for(int i = 0;i < q ; i++) cout<<ans[i]<<"\n";
