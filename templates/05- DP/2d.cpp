// construct sum i,  j using element form 1 to 64 (can use it multiple times)
const int INF = (1ll<<62);
int dp[64][64];
void init(){
  f(i,0,64) f(j,0,64) dp[i][j] = INF;
  dp[0][0] = 0;
  for(int val = 1 ; val < 60 ; val++){
        for(int x = 59 ; x >= 0 ; x--){
            for(int y = 59 ; y >= 0 ; y--){
                if(x+val < 64)
                dp[x+val][y] = min( dp[x+val][y] , (1ll<<val) + dp[x][y]);
                if(y+val < 64)
                dp[x][y+val] = min( dp[x][y+val] , (1ll<<val) + dp[x][y] );
            }
        }
  }
}
