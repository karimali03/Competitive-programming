#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3") // GCC
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")     

bool getBit(int num, int i) {
    return ((num & (1<< i)) != 0);  }

int setBit(int num, int i) {
    return num |(1 << i); }

int clearBit(int num, int i) {
    int mask =~(1 << i);
    return num & mask;  }
/*
    __builtin_popcount() count ones in binary representation of number
    _bulitinctz count trilling zeros 0000010100 = 2
    _bulitinclz() count leading zeros 0000010100 = 5
*/
void all_possible_sums(){
    int x; cin>>x;
    vector<int> v (x);
    int sum=0;
    bitset<1000005>st=1; // any array 0 can be sum 
 
    for(int i=0;i<x;i++) {
        cin>>v[i];
        sum+=v[i];
        st|=(st<<v[i]);
    }
    for(int i=0;i<=sum;i++){
       if(st[i]) {
          // this is possible sum 
       }
    }
}


//  find the XOR sum from 1 to n
ll Xor(ll n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        case 3: return 0;
    }
    return 0; 
}
// get the XOR sum of the range [L, R]
ll XorRange(ll L,ll R) {
    return Xor(R) ^ Xor(L - 1);
}
