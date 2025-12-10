string L,R;
ll dp[20][2][2][2][11][11];
// pos, tight left, tight right ,started, property
// 0 , 1 , 1 , 0 , ----
ll rec(int pos, bool tl,bool tr,bool st,int mn,int mx) {
 
    if (pos == (int)R.size())   return (st ? mx-mn : 20);
    
    ll &ret = dp[pos][tl][tr][st][mn][mx];
    if (~ret) return ret;
    ret = 20;
    
    int l = (tl ? L[pos] - '0' : 0);
    int r = (tr ? R[pos] - '0' : 9);
    for (int d = l; d <= r; d++) {
        bool ns = st || (d != 0);
        ret = min<ll>(ret , rec(pos + 1, tl && (d == l) , tr && (d == r) , ns , (ns ? min(d,mn): mn) , (ns ? max(d,mx) : mx) ) );
    }
    return ret;
}


string res;
void build(int pos, bool tl,bool tr,bool st,int mn,int mx){
    if (pos == (int)L.size()) return;
    int opt = rec(pos,tl,tr,st,mn,mx);
  
    int l = (tl ? L[pos] - '0' : 0);
    int r = (tr ? R[pos] - '0' : 9);
    for (int d = l; d <= r; d++) {
        bool ns = st || (d != 0);
        int ret = rec(pos + 1, tl && (d == l) , tr && (d == r) , ns , (ns ? min(d,mn): mn) , (ns ? max(d,mx) : mx) );
        if(ret == opt){
            res.push_back((char)d+'0');
            build(pos + 1, tl && (d == l) , tr && (d == r) , ns , (ns ? min(d,mn): mn) , (ns ? max(d,mx) : mx) );
            return;
        }
    }

}


int dp_digit(int l,int r){
    L = to_string(l);
    R = to_string(r);
    while (L.size() < R.size()) L = '0' + L;
    memset(dp,-1,sizeof(dp));
    res.clear();
    int ans = rec(0,1,1,0,10,0);
    build(0,1,1,0,10,0);
    reverse(all(res));
    while (res.back() == '0') res.pop_back();
    reverse(all(res));
    return ans;
}
