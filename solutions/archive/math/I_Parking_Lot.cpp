#include <iostream>
#include <vector>
using namespace std;

void apply_op(vector<int>& v, vector<int>& perm) {
    int n = v.size();
    vector<int> ret(n);
    for(int i = 0; i < n; i++) {
        ret[i] = v[perm[i] - 1];
    }
    v = ret;
}

vector<int> bin(int n, int k) {
    vector<int> v(n);
    for(int i = 0; i < n; i++) v[i] = i + 1;
    vector<int> perm(n);
    int od = 0, ev = n / 2;
    for(int i = 0; i < n; i++) {
        if((i + 1) & 1) perm[od++] = i + 1;
        else perm[ev++] = i + 1;
    }
    
    while(k > 0) {
        if(k & 1) apply_op(v, perm);
        apply_op(perm, perm);
        k /= 2;
    }
    return v;
}

int main() {
    int te;
    cin >> te;
    while(te--) {
        int n, k;
        cin >> n >> k;
        auto res = bin(n, k);
        for(auto x : res) cout << x << " ";
        cout << "\n";
    }
    return 0;
}