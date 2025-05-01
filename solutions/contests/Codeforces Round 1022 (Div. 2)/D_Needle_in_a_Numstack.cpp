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

int ask(int idx){
    cout<<"? "<<idx<<endl;
    cout.flush();
    int ret; cin>>ret;
    return  ret;
}

void solve(int test_case){
    int n,k; cin>>n>>k;
    map<int,int>mp;
    map<int,int>mpb;
    if((n-2*k)%k==0){
        if(n - k == k){
            cout<<"! "<<k<<" "<<k<<endl;
            return;
        }
        else{
            vi a,b;
            f(i,0,k){ 
                int ans = ask(i+1);
                mp[i+1] = ans;
                a.push_back(ans);
            }
            f(i,0,k){ b.push_back(ask(n-i));
            if(a == b) return void(cout<<"! -1"<<endl);
            reverse(all(b));
            if(a == b) return void(cout<<"! -1"<<endl);
        }
    }
    int l = k+1; int r = n-k;
    int ans = 0;
    while(l<=r){
        int mid = l + (r-l)/2;
 
        int idx = mid%k;
        if(idx == 0) idx+=k;
        int x = (mp.count(idx) ? mp[idx] : ask(idx));
        int y = (mp.count(mid) ? mp[mid] : ask(mid));
        if(x == y){
            l = mid+1;
            ans = mid;
        }
        else{
            r = mid-1;
            ans = mid-1;
        }
    }

    cout<<"! "<<ans<<" "<<n-ans<<endl;

}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}