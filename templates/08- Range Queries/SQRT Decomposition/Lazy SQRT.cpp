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
    vi blocks;
    vi lazy;

    int n,nb,cap;
    // [l , r)
    pair<int,int> blk_rng(int blk){ 
        return { blk * B , min(n , (blk+1) * B  ) };
    }  

    SQRT(int n,int k):n(n),cap(k){
        val = vi(n);
        nb = ((n-1)/B)+1;
        blocks = lazy = vi(nb);
    }

    void push(int blk){
        if(lazy[blk] == 0) return;
        auto rng = blk_rng(blk);
        blocks[blk] += lazy[blk];
        for(int i = rng.first ; i < rng.second ; i++){
            val[i] += lazy[blk];
        }
        lazy[blk] = 0;
    }

    bool chk(int l,int r){
        int x = l / B , y = r / B;
        if(x == y){
            push(x);
            for(int  i = l ; i <= r ; i++){
                if(val[i] == cap) return false;
            }
            return true;
        }
        push(x); 
        for(int i = l ; i < (x+1) * B ; i++){
            if(val[i] == cap) return false;
        }
        for(int i = x+1 ; i < y ; i++){
            if(blocks[i] + lazy[i] == cap) return false;    
        }
        push(y);
        for(int i = y*B ; i <= r ; i++){
            if(val[i] == cap) return false;
        }
        return true;
    }


    bool update(int l,int r){
        if(!chk(l,r)) return false;
        int x = l / B , y = r / B;
        if(x == y){
            for(int  i = l ; i <= r ; i++){
                val[i]++;
                blocks[x] = max(blocks[x] , val[i]);
            }  
            return true;
        }
        for(int i = l ; i < (x+1) * B ; i++){
            val[i]++;
            blocks[x] = max(blocks[x] , val[i]);
        } 
        
        for(int i = x+1 ; i < y ; i++){
            lazy[i]++;
        }
        for(int i = y*B ; i <= r ; i++){
            val[i]++;
            blocks[y] = max(blocks[y] , val[i]);
        } 
        return true;
    }
};

