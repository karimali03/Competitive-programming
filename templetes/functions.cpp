#include <bits/stdc++.h>
using namespace std;
#define ll long long 

void upper(string &s){
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

void lower(string &s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void uni(string &s){
	  auto it = unique(s.begin(), s.end());
      s.resize(distance(s.begin(), it));
}

ll sum_all(ll n,ll c=1){
    return ((n/c)*((n/c)+1)*c)/2;
}


ll fp( ll a, ll b , ll c){
	
    ll res=1;
    while(b){	
        if(b&1) res=( res%c * a%c )%c;
        a= ( a%c * a%c ) % c;
        b/=2;
    }
    return res;
}

int main(){
	
	return 0;
	
	}
