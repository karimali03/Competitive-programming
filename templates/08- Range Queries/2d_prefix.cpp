
const int N = 505;
char v[N][N];
int pre[N][N];
int n,m,k; 

void init() {
    f(i,0,n+1) f(j,0,m+1) pre[i][j] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pre[i][j] = (v[i][j] == 'g')
                      + pre[i][j - 1]
                      + pre[i - 1][j]
                      - pre[i - 1][j - 1];
        }
    }
}

int query(int from_x,int from_y,int to_x,int to_y) {
    from_x = max(1ll , from_x); from_y = max(1ll , from_y);
    to_x = min(n , to_x);  to_y = min( m , to_y);
    return pre[to_x][to_y] - pre[from_x - 1][to_y] 
           - pre[to_x][from_y-1] + pre[from_x-1][from_y-1]; 
}
