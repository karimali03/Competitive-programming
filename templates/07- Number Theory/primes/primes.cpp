// sqrt(n)
bool isprime(int n){
    if(n < 2) return false;
    for(int i = 2 ; i*i <= n ; i++){
        if(n%i == 0) return false;
    }
    return true;
}

const int N = 2e6 + 5;
int prime[N];
vector<int>primes;

// Sieve algorithm O(n*log(log(n)))
void sieve(){
    fill(prime,prime+N,1);
    prime[0] = prime[1] = 0;
    for(int i = 2 ; i*i < N ; i++){
        if(prime[i])
        for(int j = i*i ; j < N ; j += i) prime[j] = 0;
    }
    
    for(int i = 2 ; i < N ; i++) if(prime[i]) primes.push_back(i);
}

// spf ( smallest prime factor )
int spf[N];
int p[N]; // p[i] will store the total number of prime factors of i
//  O(n*log(log(n)))
void SPF(){
    for(int i = 2 ; i < N ; i++) spf[i] = i;
    for(int i = 2 ; i*i < N ; i++){
        if(spf[i] == i) 
        // start at i*i because smaller multiples are already marked by smaller primes.
        for(int j = i*i ; j < N ; j += i) if(spf[j] == j) spf[j] = i;
    }
    //  DP to count total prime factors
    p[1] = 0;
    for(int i = 2 ; i < N ; i++){
        p[i] = 1 + p[i / spf[i]];
    }
}
// log(n)
map<int,int> fast_fact(int n){
    map<int,int>ret;
    while(n > 1){
        ret[spf[n]]++;
        n /= spf[n];
    }
    return ret;
}

// largest prime factor
int lpf[N]{};
// ( N log(log(n) ) because we skip composites and only process primes
void LPF(){
    for(int i = 2 ; i < N ; i++){
        if(lpf[i]) continue;
        for(int j = i; j < N ; j += i) lpf[j] = i;
    }
}

 

map<int, int> fact(int n) {  // O(sqrt(n))
    map<int, int> res;
    
    for (int p = 2; p * p <= n; p++) {
        while (n % p == 0) {
            res[p]++;
            n /= p;
        }
    }
    if (n > 1) res[n]++; 
    
    return res;
}


vector<int> fact(int x){
    vector<int>ret;
    for (ll i = 2; i*i <= x; ++i) {
        while (x % i == 0){
            x /= i;
            ret.push_back(i);
        }
    }
    if(x > 1)ret.push_back(x);
    return ret;
}  
