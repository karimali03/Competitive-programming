#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int N=1e6+5;

vector<int>prime(N,1);
vector<int>primes;
 void sieve(){
	 
 for(int i=2;i*i<=N;i++){
    if(prime[i])  
	  for(int j=i*i;j<=N;j+=i)    prime[j]=0;    
   }
    for(int i=2;i<=N;i++) if(prime[i]) primes.push_back(i);   
      
     }       

int main(){
	sieve();
	cout<<primes[1000];
	return 0; 
}
