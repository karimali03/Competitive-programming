#include <bits/stdc++.h>
#include <iostream>
#define int long long 
using namespace std;


// get divisors of n
vector<int> divisiors(int n){ // O( sqrt(n) )
    vector<int>res;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            res.push_back(i);
            if(i!=n/i) res.push_back(n/i);
        }
    }
    return res;
}


// get divisors form factorization

vector<pair<int,int>>v;  // {prime,count}
vector<int>divisors;
void get_divisors(int idx ,int val=1){  // O ( n^(1/3) )

    if(idx == v.size()) {
        divisors.push_back(val);
        return;
    }

    for(int i=0;i<=v[idx].second ;i++){
        get_divisors(idx+1,val);
        val*=v[idx].first;
    }
    
}

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
vector<int>spf(N);   
 void SPF(){   //  O(n*log(log(n)))
    for(int i=1;i<N;i++) spf[i]=i;

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

int gcd (int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
 
int LCM(int a,int b){
    return a / gcd(a,b) * b;
}

int bin_gcd(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}





signed main(){
    
    
    return 0;
}
