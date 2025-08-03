// check number is prime 
bool isprime(int n){    // O( sqrt(n) )
    if(n<=1) return false;
    for(int i=2;i*i<=n;i++){
        if(n%i==0) return false;
    }
    return true;
}




const int N=2e6+5;

vector<int>prime(N,1);
vector<int>primes;
 void sieve(){    // Sieve algorithm O(n*log(log(n)))

  for(int i=2;i*i<=N;i++){
            if(prime[i])  
            for(int j=i*i;j<=N;j+=i)    prime[j]=0;    
   }
    for(int i=2;i<=N;i++) if(prime[i]) primes.push_back(i);   
}       


// spf ( smallest prime factor )
vector<int>spf(N+5);   
 void SPF(){   //  O(n*log(log(n)))
    for(int i=1;i<=N;i++) spf[i]=i;

     for(int i=2; i*i<=N; i++)
    {
        if(spf[i]==i)
           for(int j=i*i; j<=N; j+=i)
               if(spf[j]==j)   spf[j]=i;
    }
 }


 map<int,int> fast_fact(int n){   // O ( log(n) )
     map<int,int>res;
     while (n>1)
     {
        res[spf[n]]++;
        n/=spf[n];
     }
     return res;
     
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
