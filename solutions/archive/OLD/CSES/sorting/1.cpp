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
const int dx[8]={0, 0, 1, -1, 1, -1, -1, 1};
const int dy[8]={1, -1, 0, 0, 1, -1, 1, -1};
const char dir[4]={'R','L','D','U'};
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
// Think twice code once
 
void testCase(){
   set<int>s;
   int n; cin>>n;
   while(n--){
       int a; cin>>a;
       s.insert(a);
   }
   cout<<s.size();
}
int main() {
    NeedForSpeed;
    //  int t; cin>>t; f(i,0,t)
    testCase();  return 0;
}