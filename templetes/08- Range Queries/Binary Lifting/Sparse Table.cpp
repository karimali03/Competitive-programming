const int N = 200005;
const int LOG = 20;
int rmq[N][LOG];  

// 1 index
void build_rmq(int n){
    for (int i = 1; i <= n; i++) {
        rmq[i][0] = i;
    }
    for (int k = 1; k < LOG; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++){
            int left_idx = rmq[i][k - 1];
            int right_idx = rmq[i + (1 << (k - 1))][k - 1];
            if (a[left_idx] >= a[right_idx]) {
                rmq[i][k] = left_idx;
            } else {
                rmq[i][k] = right_idx;
            }
        }
    }
}

int query(int l, int r){
    int len = r - l + 1;
    //  63 - __builtin_clzll(len) for long long  
    int k = 31 - __builtin_clz(len); 
    int left_idx = rmq[l][k];
    int right_idx = rmq[r - (1 << k) + 1][k];

    if (a[left_idx] >= a[right_idx]) {
        return left_idx;
    } else {
        return right_idx;
    }
}

