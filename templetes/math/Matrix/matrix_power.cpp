const int MOD = 1e9+7;
struct Matrix {
    int rows, cols;
    vector<vector<int>> a;
    Matrix(){}; 
    Matrix(int r, int c) : rows(r), cols(c), a(r, vector<int>(c)) {}
 
    Matrix operator*(const Matrix &other) const {
        assert(cols == other.rows); 
        Matrix ret(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int k = 0; k < cols; k++) {
                for (int j = 0; j < other.cols; j++) {
                    (ret.a[i][j] += a[i][k] * other.a[k][j])%=MOD;
                }
            }
        }
        return ret;
    }
};
 
Matrix expo(Matrix &x,int k){
    Matrix ret(x.rows,x.cols);
    f(i,0,x.rows) ret.a[i][i] = 1;
    while(k > 0){
        if(k & 1) ret = ret * x;
        x = x * x;  k>>=1;
    }
    return ret;
}
