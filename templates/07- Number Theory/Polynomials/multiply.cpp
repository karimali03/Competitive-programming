vector<int> multiply(vector<int> A,vector<int> B,int limit){
    int m = A.size();
    int n = B.size();
    int sz = min(n + m - 1 , limit +1);
    vector<int> prod(sz, 0);
    for(int i = 0; i < min(m,sz) ; i++){
        for(int j = 0;j < n ; j++){
            if(i+j > limit) break;
            prod[i+j] += A[i] * B[j];
        }
    }
    return prod;
}
