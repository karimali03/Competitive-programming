string L,R;
ll dp[20][2][2][2];
// pos, tight left, tight right ,started, property
// 0 , 1 , 1 , 0 , ----
ll rec(int pos, bool tl,bool tr,bool st) {
    if (pos == (int)b.size()) return 1;
    ll &ret = dp[pos][tl][tr][st];
    if (~ret) return ret;
    ret = 0;

    int l = (tl ? L[pos] - '0' : 0);
    int r = (tr ? R[pos] - '0' : 9);
    for (int d = l; d <= r; d++) {
        bool ns = st || (d != 0);
        ret = max(ret , rec(pos + 1, tl && (d == l), ns , tr && (d == r)));
    }
    return ret;
}

int dp_digit(int l,int r){
    L = to_string(l);
    R = to_string(r);
    while (L.size() < R.size()) L = '0' + L;
    memset(dp,-1,sizeof(dp));
    return rec(0,1,1,0);
}
