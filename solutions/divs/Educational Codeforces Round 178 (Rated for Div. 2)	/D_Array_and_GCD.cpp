#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}


const int N=1e7+5;

vector<int>prime(N,1);
vector<int>primes;
void sieve(){    // Sieve algorithm O(n*log(log(n)))

 for(int i=2;i*i<=N;i++){
    if(prime[i])  
	  for(int j=i*i;j<=N;j+=i)    prime[j]=0;    
   }
    for(int i=2;i<=N;i++) if(prime[i]) primes.push_back(i);   

}       


void solve(int test_case){
    int n; cin>>n;
    vi v(n); cin>>v;
    int sum = 0;
   
    sort(rall(v));
    int j = 0;
    int res = 0;
    for(int i = 0 ; i < n  ; i++){
        if(primes[j] <= v[i]) sum+=(v[i]-primes[j++]);
        else if( abs(v[i]-primes[j]) <= sum)  sum-=abs(v[i]-primes[j++]);
        else return void(cout<<n-i<<ln);
    }
    cout<<0<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    sieve();
   // cout<<primes.size()<<ln;
    cin >> t;
    for (int i = 1; i <= t; i++) {
       solve(i);
    }
    return 0;
}