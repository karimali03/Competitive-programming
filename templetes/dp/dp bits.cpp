const int MOD = 1e9+7;
// dp[pos][t1L][t1R][t2L][t2R][t3L][t3R]
ll dp[32][2][2][2][2][2][2];
string L1,R1,L2,R2,L3,R3;

ll rec(int pos,int t1L,int t1R,int t2L,int t2R,int t3L,int t3R) {
    if(pos==32) return 1; // reached end, valid

    ll &ret = dp[pos][t1L][t1R][t2L][t2R][t3L][t3R];
    if(~ret) return ret;
    ret = 0;

    int low1  = t1L ? (L1[pos]-'0') : 0;
    int high1 = t1R ? (R1[pos]-'0') : 1;
    int low2  = t2L ? (L2[pos]-'0') : 0;
    int high2 = t2R ? (R2[pos]-'0') : 1;
    int low3  = t3L ? (L3[pos]-'0') : 0;
    int high3 = t3R ? (R3[pos]-'0') : 1;

    for(int d1=low1; d1<=high1; d1++){
        for(int d2=low2; d2<=high2; d2++){
            for(int d3=low3; d3<=high3; d3++){
                if((d1^d2^d3)!=0) continue;
                ret += rec(
                    pos+1,
                    t1L && (d1==low1), t1R && (d1==high1),
                    t2L && (d2==low2), t2R && (d2==high2),
                    t3L && (d3==low3), t3R && (d3==high3)
                );
                if(ret>=MOD) ret-=MOD;
            }
        }
    }
    return ret;
}

ll calc(int l1,int r1,int l2,int r2,int l3,int r3){
    // turn into 32-bit binary strings
    L1 = bitset<32>(l1).to_string();
    R1 = bitset<32>(r1).to_string();
    L2 = bitset<32>(l2).to_string();
    R2 = bitset<32>(r2).to_string();
    L3 = bitset<32>(l3).to_string();
    R3 = bitset<32>(r3).to_string();

    memset(dp,-1,sizeof(dp));
    return rec(0,1,1,1,1,1,1);
}

