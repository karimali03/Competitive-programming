// Function to find the transpose of a matrix
// Time Complexity: O(n^2)
void trans(vii & v ,int n){
    for(int i  = 0 ; i <  n; i++){
        for(int j = i+1 ; j <  n;  j++){
            swap(v[i][j],v[j][i]);
        }
    }
}
