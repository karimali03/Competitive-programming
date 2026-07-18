/*
 Index-to-Block:
   - block_id = idx / block_size
 Block-to-Index:
   - block_start = block_id * block_size
   - block_end = min(n - 1, (block_id + 1) * block_size - 1)
*/
struct SQRT{
    static const int B = 300;
    vi val;
    vector<pair<int,int>> blocks;

    int n,nb;
    // [l , r)
    pair<int,int> blk_rng(int blk){ 
        return { blk * B , min(n , (blk+1) * B  ) };
    }  

    SQRT(vi &v){
        val = v;
        n = v.size();
        nb = ((n-1)/B)+1;
        blocks = vector<pair<int,int>>(nb,pair<int,int>(-1,-1));
        for(int i = 0;i < n ; i++){
            auto cur = make_pair(v[i],i);
            blocks[i/B] = max(blocks[i/B],cur);
        }
    }

    void update(int x,int y){
        auto rng = blk_rng(x/B);
        val[x] = y;
        for(int i = rng.first ; i  < rng.second ; i++){
            auto cur = make_pair(val[i],i);
            blocks[i/B] = max(blocks[i/B],cur);
        }
    }

    pair<int,int> query(int l,int r){
        int x = l / B , y = r / B;
        pair<int,int> ret = make_pair(-1,-1);
        if(x == y){
            for(int  i = l ; i <= r ; i++){
                auto cur = make_pair(val[i],i);
                ret = max(ret , cur);
            }
            return ret;
        }

        for(int i = l ; i < (x+1) * B ; i++){
            auto cur = make_pair(val[i],i);
            ret = max(ret , cur);
        }
        for(int i = x+1 ; i < y ; i++){
            ret = max(ret , blocks[i]);
        }
        for(int i = y*B ; i <= r ; i++){
            auto cur = make_pair(val[i],i);
            ret = max(ret , cur);
        }
        return ret;
    }
};
