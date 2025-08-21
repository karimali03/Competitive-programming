#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define NeedForSpeed ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define ll long long
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define vl vector<ll>
#define vll vector<vector<ll>>
#define pq priority_queue
#define ln "\n"
#define ld long double
#define S second
#define F first
#define p pair
#define all(x) x.begin(), x.end()
#define gcd(a,b)  __gcd(a,b)
#define lcm(a,b)   (a*b/__gcd(a,b))
#define f(i,a,b) for(int i=a;i<b;i++)
#define fl(i,a,b) for(ll i=a;i<b;i++)
#define tll tuple<ll,ll,ll>
const int dx[8]={0, 0, 1, -1, 1, -1, -1, 1};
const int dy[8]={1, -1, 0, 0, 1, -1, 1, -1};
 
void file(){
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
}
void upper(string &s){
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}
void lower(string &s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}
int ask(int i,int j){
    cout<<"? "<<i<<" "<<j<<endl;
    cout.flush();
    int ret; cin>>ret;
    return  ret;
}
ll sum_all(ll n,ll c=1){
    return ((n/c)*((n/c)+1)*c)/2;
}
const int oo=INT_MAX;
/*
const int N=1e6+1;
vl spf(N+1);
 vi primes(N+1,1);
  vi prime;
void sieve(){
    for(ll i=0;i<=N;i++) spf[i]=i;
    for(ll i=2;i<=N;i++){
        if(spf[i]==i){
            for(ll j=i*i;j<=N;j+=i) spf[j]=i;
        }
    }
}
map<int,int> pre_fact(int num){
    map<int,int>mp;
    while(num>1){
        mp[spf[num]]++;
        num/=spf[num];
    }
    return mp;
}
*/
// Think twice code once
 
void testCase() {
   int n,k; cin>>n>>k;
   vi a(n);
   f(i,0,n) cin>>a[i];
    sort(all(a));
    int i=0,j=n-1;
    int cnt=0;
    while(j>i){
        if(a[i]+a[j]<=k) cnt++,j--,i++;
        else cnt++,j--;
    }
    if(j==i) cnt++;
    cout<<cnt<<ln;
}
int main() {
    file();
    NeedForSpeed;
 //  int t; cin>>t; while(t--)
        testCase();  return 0;
}
 
 
 